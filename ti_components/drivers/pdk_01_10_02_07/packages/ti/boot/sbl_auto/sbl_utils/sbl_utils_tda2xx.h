/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup SBL_TDA2XX_UTILS TDA2xx SBL Utilities
 *
 *  @{
 */
/**
 *  \file     sbl_utils_tda2xx.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDA2xx SOC
 *            family. This also contains some related macros, structures and
 *            enums.
 */

#ifndef SBL_UTILS_TDA2XX_H_
#define SBL_UTILS_TDA2XX_H_

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

/* IODelay register offsets for TDA2xx platform */
#define CONFIG_REG_0                                (uint32_t) (0x0000000CU) /**< CONFIG_REG_0 */
#define CONFIG_REG_1                                (uint32_t) (0x00000010U) /**< CONFIG_REG_1 */
#define CONFIG_REG_2                                (uint32_t) (0x00000014U) /**< CONFIG_REG_2 */
#define CONFIG_REG_3                                (uint32_t) (0x00000018U) /**< CONFIG_REG_3 */
#define CONFIG_REG_4                                (uint32_t) (0x0000001CU) /**< CONFIG_REG_4 */
#define CONFIG_REG_8                                (uint32_t) (0x0000002CU) /**< CONFIG_REG_8 */

/* Fields for CONFIG_REG_0 */
#define CONFIG_REG_0_CALIBRATION_START_MASK         (0x00000001U) /**< CONFIG_REG_0_CALIBRATION_START_MASK */
#define CONFIG_REG_0_CALIBRATION_START_SHIFT        (0U) /**< CONFIG_REG_0_CALIBRATION_START_SHIFT */

#define CONFIG_REG_0_ROM_READ_MASK                  (0x00000002U) /**< CONFIG_REG_0_ROM_READ_MASK */
#define CONFIG_REG_0_ROM_READ_SHIFT                 (1U) /**< CONFIG_REG_0_ROM_READ_SHIFT */

/* Fields for CONFIG_REG_2 */
#define CONFIG_REG_2_REFCLK_PERIOD_MASK             (0x0000FFFFU) /**< CONFIG_REG_2_REFCLK_PERIOD_MASK */
#define CONFIG_REG_2_REFCLK_PERIOD_SHIFT            (0U) /**< CONFIG_REG_2_REFCLK_PERIOD_SHIFT */

/* Fields for CONFIG_REG_3 */
#define CONFIG_REG_3_COARSE_REF_COUNT_MASK          (0x0000FFFFU) /**< CONFIG_REG_3_COARSE_REF_COUNT_MASK */
#define CONFIG_REG_3_COARSE_REF_COUNT_SHIFT         (0U) /**< CONFIG_REG_3_COARSE_REF_COUNT_SHIFT */

#define CONFIG_REG_3_COARSE_DELAY_COUNT_MASK        (0xFFFF0000U) /**< CONFIG_REG_3_COARSE_DELAY_COUNT_MASK */
#define CONFIG_REG_3_COARSE_DELAY_COUNT_SHIFT       (16U) /**< CONFIG_REG_3_COARSE_DELAY_COUNT_SHIFT */

/* Fields for CONFIG_REG_4 */
#define CONFIG_REG_4_FINE_REF_COUNT_MASK            (0x0000FFFFU) /**< CONFIG_REG_4_FINE_REF_COUNT_MASK */
#define CONFIG_REG_4_FINE_REF_COUNT_SHIFT           (0U) /**< CONFIG_REG_4_FINE_REF_COUNT_SHIFT */

#define CONFIG_REG_4_FINE_DELAY_COUNT_MASK          (0xFFFF0000U) /**< CONFIG_REG_4_FINE_DELAY_COUNT_MASK */
#define CONFIG_REG_4_FINE_DELAY_COUNT_SHIFT         (16U) /**< CONFIG_REG_4_FINE_DELAY_COUNT_SHIFT */

/* ISOIN Field for CTRL_CORE_SMA_SW_0 */
#define CTRL_CORE_SMA_SW_0_ISOIN_MASK               (0x00000004U) /**< CTRL_CORE_SMA_SW_0_ISOIN_MASK */
#define CTRL_CORE_SMA_SW_0_ISOIN_SHIFT              (2U) /**< CTRL_CORE_SMA_SW_0_ISOIN_SHIFT */

/* Lock and Unlock values for Global lock : CONFIG_REG_8 */
#define CONFIG_REG_8_LOCK_GLOBAL_LOCK               (0x0000AAABU) /**< CONFIG_REG_8_LOCK_GLOBAL_LOCK */
#define CONFIG_REG_8_UNLOCK_GLOBAL_LOCK             (0x0000AAAAU) /**< CONFIG_REG_8_UNLOCK_GLOBAL_LOCK */

/* Lock and Unlock values for MMR_LOCK1 */
#define LOCK_MMR_LOCK1                              (0x1A1C8144U) /**< LOCK_MMR_LOCK1 */
#define UNLOCK_MMR_LOCK1                            (0x2FF1AC2BU) /**< UNLOCK_MMR_LOCK1 */

/* Lock and Unlock values for MMR_LOCK5 */
#define LOCK_MMR_LOCK5                              (0x143F832CU) /**< LOCK_MMR_LOCK5 */
#define UNLOCK_MMR_LOCK5                            (0x6F361E05U) /**< UNLOCK_MMR_LOCK5 */

/* Reference clock period for sysclk1 of 20 MHz */
#define REFCLK_PERIOD_SYSCLK1_20MHZ                 (0x00002710U) /**< REFCLK_PERIOD_SYSCLK1_20MHZ */

/* Reference clock period for L4 ICLK of 66.5 MHz */
#define REFCLK_PERIOD_L4ICLK_66_5_MHZ               (0x000005DEU) /**< REFCLK_PERIOD_L4ICLK_66_5_MHZ */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief   This structure defines the delay configuration for IO Delay Config
 *           Registers: CFG_X_IN, CFG_X_OUT and CFG_X_OEN.
 */
typedef struct sblutilsDelayConfig
{
    uint16_t offset;
    /**< Offset for Delay Configuration Register */
    uint16_t aDelay;
    /**< Value of Process Agnostic(Unaware) Delay */
    uint16_t gDelay;
    /**< Value of Process Gnostic(Aware) Delay */
}sblutilsDelayConfig_t;

/**
 *  \brief This structure defines the delay configuration associated with a
 *         particular pad as given by PCT (Pad Configuration Tool).
 */
typedef struct sblutilsPadDelayConfig
{
    uint16_t              offset;
    /**< Offset for Pad Configuration Register */
    uint32_t              regVal;
    /**< Value of Pad configuration Register as given by PCT */
    sblutilsDelayConfig_t delayConfigIn;
    /**< Delay Configuration of CFG_X_IN register */
    sblutilsDelayConfig_t delayConfigOen;
    /**< Delay Configuration of CFG_X_OEN register */
    sblutilsDelayConfig_t delayConfigOut;
    /**< Delay Configuration of CFG_X_OUT register */
}sblutilsPadDelayConfig_t;

/**
 *  \brief   This structure is used to store the calculated delay values to be
 *           configured in CFG_X_IN, CFG_X_OUT and CFG_X_OEN Registers.
 */
typedef struct sblutilsDelayConfigRegValue
{
    uint32_t configRegValueIn;
    /**< Calculated value to be configured in CFG_X_IN register */
    uint32_t configRegValueOen;
    /**< Calculated value to be configured in CFG_X_OEN register */
    uint32_t configRegValueOut;
    /**< Calculated value to be configured in CFG_X_OUT register */
}sblutilsDelayConfigRegValue_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function implements IODelay Recalibration.
 *          IODelay re-calibration is required due to change in AVS0 voltage,
 *          otherwise there is some IO timing error versus datasheet.
 *
 * \param   bootMode    Boot Mode with which SBL has been built.
 *
 * \return  None.
 */
void SBLUtilsScaleIODelay(uint32_t bootMode);

/**
 * \brief   This function get called in beginning of SBL. It refreshes the
 *          WDT to 3 mins, configures the delay event to 2 mins &
 *          registers the ISR handler.
 *
 * \return  None.
 */
void SBLUtilsWDTimerBegin(void);

/**
 * \brief   This function is delay event ISR. It refreshes the WDT to 3 mins &
 *          sets the delay to 2 mins.
 *
 * \param   ptr     Pointer to ISR.
 *
 * \return  None.
 */
void SBLUtilsWDTimerIsr(void *ptr);

/**
 * \brief   This function get called at the end of boot process. It
 *          un-registers the delay event ISR & disables the interrupt. It
 *          refreshes the WDT overflow value to 3 mins. Application has to
 *          take care of WDT
 *
 * \return  None.
 */
void SBLUtilsWDTimerEnd(void);

/** \brief Function to configure the static dependencies from master clock
 *         domains to slave clock domains.
 *
 *  \return Status of the API.
 *
 */
/**
 * \brief   This function configures the static dependencies from master clock
 *          domains to slave clock domains.
 *
 * \return  status         STW_SOK: Pass
 *                         STW_EFAIL: Failure
 */
int32_t SBLUtilsConfigStaticDependency(void);

/**
 * \brief   This function returns the address of the pad config object and
 *          size of it to be used for a SOC.
 *
 * \param   padArraySize        Pointer to return size of pad config Object
 *
 * \param   bootMode            Boot Mode with which SBL is built
 *
 * \return  Pointer to pad config object
 */
sblutilsPadDelayConfig_t *SBLUtilsGetPadDelayConfigStruct(
    uint32_t *padArraySize, uint32_t bootMode);

/**
 * \brief   This function calculates the config value based on the Virtual and
 *          Manual mode delay values using the PCT and updates in same Object.
 *
 * \param   padDelayConfig      Pad config object array
 * \param   padArraySize        Number of elements in pad config Object
 *
 * \return  pointer to object sblutilsDelayConfigRegValue_t filled with the
            calculated delay config values to be programmed.
 */
sblutilsDelayConfigRegValue_t *SBLUtilsGetDelayConfigRegValStruct(
    sblutilsPadDelayConfig_t padDelayConfig[],
    uint32_t                 padArraySize);
/**
 * \brief   This function configures the SoC PAD Mux along with Virtual and
 *          Manual mode delays. padDelayRegValue object should be updated with
 *          config values using the SBLUtilsGetDelayConfigRegValStruct API
 *          before calling this function.
 *
 * \param   padDelayConfig      Pad config object array
 * \param   padDelayRegValue    calculated delau config value object array
 * \param   padArraySize        Number of elements in pad config Object
 *
 * \return  None
 */
void SBLUtilsConfigPadMux(sblutilsPadDelayConfig_t      padDelayConfig[],
                          sblutilsDelayConfigRegValue_t padDelayRegValue[],
                          uint32_t                      padArraySize);

#ifdef __cplusplus
}

#endif

#endif
/* @} */

