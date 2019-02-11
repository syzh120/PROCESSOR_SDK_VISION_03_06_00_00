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
 *  \file     sbl_utils_tda3xx_ddr_config.c
 *
 *  \brief    This file contains the SBL Utility layer for configuring DDR for
 *            TDA3xx platform. This is taken from gel and follows the Gel coding
 *            guidelines which are different from starterware coding guidelines.
 */

/* Derived from GEL commit ID: 67e4b5d8516d960255ee67d4937066d37550f0c3 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_emif.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_ddr_config.h>
#include <sbl_utils_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ENABLE_ECC              (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SBLGetOppId(uint32_t packageType);

#ifdef __cplusplus
}
#endif

static void us_delay(uint32_t delay);
static void TDA3xx_CM_DDRIO_Config(uint32_t mode);
static void TDA3xx_reset_emif_params_ddr3_532(uint32_t base_addr);
static void TDA3xx_set_emif_params_ddr3_532(uint32_t base_addr);
static void TDA3xx_reset_emif_params_ddr3_400(uint32_t base_addr);
static void TDA3xx_set_emif_params_ddr3_400(uint32_t base_addr);
static void TDA3xx_reset_emif_params_ddr3_333(uint32_t base_addr);
static void TDA3xx_set_emif_params_ddr3_333(uint32_t base_addr);
static void TDA3xx_reset_emif_params_ddr2_400(uint32_t base_addr);
static void TDA3xx_set_emif_params_ddr2_400(uint32_t base_addr);
static void TDA3xx_reset_emif_params_ddr2_333(uint32_t base_addr);
static void TDA3xx_set_emif_params_ddr2_333(uint32_t base_addr);
static void TDA3xx_reset_emif_params_lpddr2_400(uint32_t base_addr);
static void TDA3xx_set_emif_params_lpddr2_400(uint32_t base_addr);
static void TDA3xx_reset_emif_params_lpddr2_333(uint32_t base_addr);
static void TDA3xx_set_emif_params_lpddr2_333(uint32_t base_addr);
static void EMIF_Config(uint32_t base_addr,
                        uint32_t mode,
                        uint32_t isHwLevelingEnabledInput,
                        uint32_t isEccEnabled);
static void EMIF_LPDDR2_Config(uint32_t base_addr);
static void EMIF_DDR3_UpdateHWLevelOutput(uint32_t base_addr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t HW_LEVELING_ENABLED = 1U;
/*
 * Following registers are derived from other parameters and should not be
 * defined
 * directly:
 * EXT_PHY_CTRL_1
 * DDR_PHY_CTRL_1
 * EXT_PHY_CTRL_22
 * EXT_PHY_CTRL_23
 * EXT_PHY_CTRL_24
 * EXT_PHY_CTRL_25
 */
static uint32_t SDRAM_TIM_1;
static uint32_t SDRAM_TIM_2;
static uint32_t SDRAM_TIM_3;
static uint32_t LPDDR2_NVM_TIM;
static uint32_t PWR_MGMT_CTRL;
static uint32_t OCP_CONFIG;
static uint32_t IODFT_TLGC;
static uint32_t DLL_CALIB_CTRL;
static uint32_t ZQ_CONFIG;
static uint32_t TEMP_ALERT_CONFIG; /* Not supported in DRA75x_74x,
                                    * DRA72x, TDA2x, TDA2Ex */
static uint32_t RDWR_LVL_RMP_WIN;
static uint32_t DDR_PHY_CTRL_2;
static uint32_t PRI_COS_MAP;
static uint32_t CONNID_COS_1_MAP;
static uint32_t CONNID_COS_2_MAP;
static uint32_t RD_WR_EXEC_THRSH;
static uint32_t COS_CONFIG;
static uint32_t EXT_PHY_CTRL_2;
static uint32_t EXT_PHY_CTRL_3;
static uint32_t EXT_PHY_CTRL_4;
static uint32_t EXT_PHY_CTRL_5;
static uint32_t EXT_PHY_CTRL_6;
static uint32_t EXT_PHY_CTRL_7;
static uint32_t EXT_PHY_CTRL_8;
static uint32_t EXT_PHY_CTRL_9;
static uint32_t EXT_PHY_CTRL_10;
static uint32_t EXT_PHY_CTRL_11;
static uint32_t EXT_PHY_CTRL_12;
static uint32_t EXT_PHY_CTRL_13;
static uint32_t EXT_PHY_CTRL_14;
static uint32_t EXT_PHY_CTRL_15;
static uint32_t EXT_PHY_CTRL_16;
static uint32_t EXT_PHY_CTRL_17;
static uint32_t EXT_PHY_CTRL_18;
static uint32_t EXT_PHY_CTRL_19;
static uint32_t EXT_PHY_CTRL_20;
static uint32_t EXT_PHY_CTRL_21;
static uint32_t EXT_PHY_CTRL_26;
static uint32_t EXT_PHY_CTRL_27;
static uint32_t EXT_PHY_CTRL_28;
static uint32_t EXT_PHY_CTRL_29;
static uint32_t EXT_PHY_CTRL_30;
static uint32_t EXT_PHY_CTRL_31;
static uint32_t EXT_PHY_CTRL_32;
static uint32_t EXT_PHY_CTRL_33;
static uint32_t EXT_PHY_CTRL_34;
static uint32_t EXT_PHY_CTRL_35;
static uint32_t EXT_PHY_CTRL_36;

static uint32_t SDRAM_REF_CTRL;
/* Example calculation:
 * For 7.8us at 532MHz : Value = 7.8u*532M = 0x1035
 */

static uint32_t SDRAM_CONFIG_2;
static uint32_t SDRAM_CONFIG;

/* Fields in DDR_PHY_CTRL_1 */
/* Bit[21] - calculated using DataMacro/MDLL clock ratio
 * Set to 1 for 532M, so that PHY DLL runs at 266.
 * Set to 0 for 400M, so that PHY DLL runs at 400M.
 * Ensure PHY DLL lower limit of 266M is not violated.
 */
static uint32_t EMIF_PHY_HALF_DELAY_MODE;
static uint32_t EMIF_PHY_DIS_CALIB_RST;    /* Bit[19]    */
static uint32_t EMIF_PHY_INVERT_CLKOUT;    /* Bit[18]    */
static uint32_t EMIF_PHY_DLL_LOCK_DIFF;    /* Bit[17:10] */
static uint32_t EMIF_PHY_FAST_DLL_LOCK;    /* Bit[9]     */
static uint32_t EMIF_PHY_READ_LATENCY;     /* Bit[4:0], Typically >= (CL + 4) */

static uint32_t EMIF_PHY_USE_RANK0_DELAYS; /* Set to 1 if using ddr1_csn[0]
                                            * only.
                                            * Set to 0 otherwise.
                                            * ddr1_csn[1] is not supported on
                                            * DRA75x_74x, TDA2x, TDA3x.
                                            */
static uint32_t EMIF_PHY_CTRL_SLAVE_RATIO;
static uint32_t EMIF_PHY_DQ_OFFSET;
static uint32_t EMIF_PHY_GATELVL_INIT_MODE;
static uint32_t EMIF_PHY_FIFO_WE_IN_DELAY;    /* Only for DLL_OVERRIDE = 1 */
static uint32_t EMIF_PHY_CTRL_SLAVE_DELAY;    /* Only for DLL_OVERRIDE = 1 */
static uint32_t EMIF_PHY_RD_DQS_SLAVE_DELAY;  /* Only for DLL_OVERRIDE = 1 */
static uint32_t EMIF_PHY_WR_DQS_SLAVE_DELAY;  /* Only for DLL_OVERRIDE = 1 */
static uint32_t EMIF_PHY_WR_DATA_SLAVE_DELAY; /* Only for DLL_OVERRIDE = 1 */

/* SDRAM_REF_CTRL_INIT:
 * For DDR3:   value used initially to get 500us delay between
 *             RESET de-assertion to CKE assertion after power-up
 * For DDR2:   value used initially to get 200us delay between
 *             POWER UP and PRECHARGE ALL command
 * For LPDDR2: value used initially to get 200us delay between
 *             POWER UP and RESET command to LPDDR2
 * Example calculation:
 * For 500us delay at 532MHz : Value = 500u*532M/16 = 0x40F1
 */
static uint32_t SDRAM_REF_CTRL_INIT;

/* Following three values are applicable only when HW_LEVELING_ENABLED == 1.
 * These allows us to use a combination of HW leveling and SW leveling.
 * Currently only for debug.
 * If DISABLE_READ_LEVELING == 1
 *      Set EMIF_PHY_RD_DQS_SLAVE_RATIO registers with SW Leveling values
 * If DISABLE_READ_GATE_LEVELING == 1
 *      Set EMIF_PHY_FIFO_WE_SLAVE_RATIO registers with SW Leveling values
 * If DISABLE_WRITE_LEVELING == 1
 *      Set EMIF_PHY_WR_DQS_SLAVE_RATIO registers with SW Leveling values
 */
static uint32_t DISABLE_READ_LEVELING;
static uint32_t DISABLE_READ_GATE_LEVELING;
static uint32_t DISABLE_WRITE_LEVELING;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* The below API is meant to be used only while initializing DDR in SBL. Don't
 * use it at other places
 */
static void us_delay(uint32_t delay)
{
    uint32_t tickCount, initCount, finalCount, count;
    tickCount  = delay / 30U;
    initCount  = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    finalCount = initCount + tickCount;
    do
    {
        count = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    } while (count < finalCount);
}

static void TDA3xx_reset_emif_params_ddr3_532(uint32_t base_addr)
{
    uint32_t temp;

    EMIF_PHY_HALF_DELAY_MODE  = 1U;
    EMIF_PHY_DIS_CALIB_RST    = 0U;
    EMIF_PHY_INVERT_CLKOUT    = 1U;
    EMIF_PHY_DLL_LOCK_DIFF    = 0x10U;
    EMIF_PHY_FAST_DLL_LOCK    = 0U;
    EMIF_PHY_READ_LATENCY     = 0xBU;
    EMIF_PHY_USE_RANK0_DELAYS = 1U;

    EMIF_PHY_CTRL_SLAVE_RATIO    = 0x80U;
    EMIF_PHY_DQ_OFFSET           = 0x30U;
    EMIF_PHY_GATELVL_INIT_MODE   = 1U;
    EMIF_PHY_FIFO_WE_IN_DELAY    = 0x00U;
    EMIF_PHY_CTRL_SLAVE_DELAY    = 0x00U;
    EMIF_PHY_RD_DQS_SLAVE_DELAY  = 0x60U;
    EMIF_PHY_WR_DQS_SLAVE_DELAY  = 0x20U;
    EMIF_PHY_WR_DATA_SLAVE_DELAY = 0x00U;

    SDRAM_TIM_1 = 0xCEEF266BU;
    SDRAM_TIM_2 = 0x305A7FDAU;
    SDRAM_TIM_3 = 0x427F8558U;

    LPDDR2_NVM_TIM = 0U;
    PWR_MGMT_CTRL  = 0U;
    OCP_CONFIG     = 0x0A500000U;
    IODFT_TLGC     = HW_RD_REG32(base_addr +
                                 EMIF_IODFT_TLGC);
    DLL_CALIB_CTRL    = 0x00050000U;
    ZQ_CONFIG         = 0x5007190BU;
    TEMP_ALERT_CONFIG = HW_RD_REG32(base_addr +
                                    EMIF_TEMPERATURE_ALERT_CONFIG);
    RDWR_LVL_RMP_WIN = HW_RD_REG32(base_addr +
                                   EMIF_READ_WRITE_LEVELING_RAMP_WINDOW);

    DDR_PHY_CTRL_2 = HW_RD_REG32(base_addr +
                                 EMIF_DDR_PHY_CONTROL_2);
    PRI_COS_MAP      = 0U;
    CONNID_COS_1_MAP = 0U;
    CONNID_COS_2_MAP = 0U;
    RD_WR_EXEC_THRSH = 0x00000305U;
    COS_CONFIG       = 0x00FFFFFFU;

    /* EMIF_PHY_FIFO_WE_SLAVE_RATIO (RD_DQS_GATE) */
    temp           = 0x90U;
    EXT_PHY_CTRL_2 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_3 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_4 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_5 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_6 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_RD_DQS_SLAVE_RATIO */
    temp            = 0x44U;
    EXT_PHY_CTRL_7  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_8  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_9  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_10 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_11 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DATA_SLAVE_RATIO */
    temp = 0x7FU;
    EXT_PHY_CTRL_12 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_13 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_14 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_15 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_16 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DQS_SLAVE_RATIO */
    temp = 0x48U;
    EXT_PHY_CTRL_17 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_18 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_19 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_20 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_21 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_GATELVL_INIT_RATIO */
    temp = 0;
    EXT_PHY_CTRL_26 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_27 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_28 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_29 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_30 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WRLVL_INIT_RATIO */
    temp = 0;
    EXT_PHY_CTRL_31 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_32 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_33 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_34 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_35 = (temp << 16U) | (temp << 0U);

    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36);
    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36_SHADOW);

    SDRAM_REF_CTRL = 0x00001035U;
    SDRAM_CONFIG_2 = 0x08000000U;
    SDRAM_CONFIG   = 0x61811AB2U;

    DISABLE_READ_LEVELING      = 0U;
    DISABLE_READ_GATE_LEVELING = 0U;
    DISABLE_WRITE_LEVELING     = 0U;

    /* HW Leveling is supported in DDR3 */
    HW_LEVELING_ENABLED = 1U;
}

static void TDA3xx_reset_emif_params_ddr3_400(uint32_t base_addr)
{
    TDA3xx_reset_emif_params_ddr3_532(base_addr);
}

static void TDA3xx_reset_emif_params_ddr3_333(uint32_t base_addr)
{
    TDA3xx_reset_emif_params_ddr3_400(base_addr);
}

static void TDA3xx_reset_emif_params_lpddr2_400(uint32_t base_addr)
{
    uint32_t temp;

    EMIF_PHY_HALF_DELAY_MODE = 0U;
    EMIF_PHY_DIS_CALIB_RST   = 0U;
    EMIF_PHY_INVERT_CLKOUT   = 0U;
    EMIF_PHY_DLL_LOCK_DIFF   = 0x10U;
    EMIF_PHY_FAST_DLL_LOCK   = 1U;

    EMIF_PHY_READ_LATENCY     = 0x9U;
    EMIF_PHY_USE_RANK0_DELAYS = 1U;

    EMIF_PHY_CTRL_SLAVE_RATIO    = 0x40U;
    EMIF_PHY_DQ_OFFSET           = 0x30U;
    EMIF_PHY_GATELVL_INIT_MODE   = 1U;
    EMIF_PHY_FIFO_WE_IN_DELAY    = 0x20U;
    EMIF_PHY_CTRL_SLAVE_DELAY    = 0x80U;
    EMIF_PHY_RD_DQS_SLAVE_DELAY  = 0x40U;
    EMIF_PHY_WR_DQS_SLAVE_DELAY  = 0x00U;
    EMIF_PHY_WR_DATA_SLAVE_DELAY = 0x00U;

    SDRAM_TIM_1    = 0x4EEB05E2U;
    SDRAM_TIM_2    = 0x20370DD2U;
    SDRAM_TIM_3    = 0x42B1C337U;
    LPDDR2_NVM_TIM = 0U;
    PWR_MGMT_CTRL  = 0U;
    OCP_CONFIG     = 0x0A000000U;
    IODFT_TLGC     = HW_RD_REG32(base_addr +
                                 EMIF_IODFT_TLGC);
    DLL_CALIB_CTRL    = 0x00050000U;
    ZQ_CONFIG         = 0x500B190BU;
    TEMP_ALERT_CONFIG = HW_RD_REG32(base_addr +
                                    EMIF_TEMPERATURE_ALERT_CONFIG);
    RDWR_LVL_RMP_WIN = HW_RD_REG32(base_addr +
                                   EMIF_READ_WRITE_LEVELING_RAMP_WINDOW);

    DDR_PHY_CTRL_2 = HW_RD_REG32(base_addr +
                                 EMIF_DDR_PHY_CONTROL_2);
    PRI_COS_MAP      = 0U;
    CONNID_COS_1_MAP = 0U;
    CONNID_COS_2_MAP = 0U;
    RD_WR_EXEC_THRSH = 0x00000305U;
    COS_CONFIG       = 0x00FFFFFFU;

    /* EMIF_PHY_FIFO_WE_SLAVE_RATIO (RD_DQS_GATE) */
    temp           = 0x180U;
    EXT_PHY_CTRL_2 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_3 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_4 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_5 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_6 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_RD_DQS_SLAVE_RATIO */
    temp            = 0x34U;
    EXT_PHY_CTRL_7  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_8  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_9  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_10 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_11 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DATA_SLAVE_RATIO */
    temp = 0x60U;
    EXT_PHY_CTRL_12 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_13 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_14 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_15 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_16 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DQS_SLAVE_RATIO */
    temp = 0x20U;
    EXT_PHY_CTRL_17 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_18 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_19 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_20 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_21 = (temp << 16U) | (temp << 0U);

    /* 26-36 are updated so that uninitialized variables are not used */
    /* EMIF_PHY_GATELVL_INIT_RATIO */
    EXT_PHY_CTRL_26 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_26);
    EXT_PHY_CTRL_27 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_27);
    EXT_PHY_CTRL_28 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_28);
    EXT_PHY_CTRL_29 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_29);
    EXT_PHY_CTRL_30 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_30);

    /* EMIF_PHY_WRLVL_INIT_RATIO */
    EXT_PHY_CTRL_31 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_31);
    EXT_PHY_CTRL_32 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_32);
    EXT_PHY_CTRL_33 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_33);
    EXT_PHY_CTRL_34 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_34);
    EXT_PHY_CTRL_35 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_35);

    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36);
    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36_SHADOW);

    /* for extended temp(>85C), refresh needs to be 4X faster!! */
    SDRAM_REF_CTRL = 0x00000C30U;
    SDRAM_CONFIG_2 = 0x08000000U;
    SDRAM_CONFIG   = 0x83801A21U;

    DISABLE_READ_LEVELING      = 0U;
    DISABLE_READ_GATE_LEVELING = 0U;
    DISABLE_WRITE_LEVELING     = 0U;

    /* HW Leveling is not supported in LPDDR2 */
    HW_LEVELING_ENABLED = 0U;
}

static void TDA3xx_reset_emif_params_lpddr2_333(uint32_t base_addr)
{
    TDA3xx_reset_emif_params_lpddr2_400(base_addr);
}

static void TDA3xx_reset_emif_params_ddr2_400(uint32_t base_addr)
{
    uint32_t temp;

    EMIF_PHY_HALF_DELAY_MODE = 1U;
    EMIF_PHY_DIS_CALIB_RST   = 0U;
    EMIF_PHY_INVERT_CLKOUT   = 1U;
    EMIF_PHY_DLL_LOCK_DIFF   = 0x10U;
    EMIF_PHY_FAST_DLL_LOCK   = 0U;

    EMIF_PHY_READ_LATENCY     = 0xAU;
    EMIF_PHY_USE_RANK0_DELAYS = 1U;

    EMIF_PHY_CTRL_SLAVE_RATIO    = 0x80U;
    EMIF_PHY_DQ_OFFSET           = 0x33U;
    EMIF_PHY_GATELVL_INIT_MODE   = 1U; /* To avoid uninitialized usage */
    EMIF_PHY_FIFO_WE_IN_DELAY    = 1U; /* To avoid uninitialized usage */
    EMIF_PHY_CTRL_SLAVE_DELAY    = 1U; /* To avoid uninitialized usage */
    EMIF_PHY_RD_DQS_SLAVE_DELAY  = 1U; /* To avoid uninitialized usage */
    EMIF_PHY_WR_DQS_SLAVE_DELAY  = 1U; /* To avoid uninitialized usage */
    EMIF_PHY_WR_DATA_SLAVE_DELAY = 1U; /* To avoid uninitialized usage */

    SDRAM_TIM_1    = 0x6AAB15DAU;
    SDRAM_TIM_2    = 0x202D31D2U;
    SDRAM_TIM_3    = 0x5060029FU;
    LPDDR2_NVM_TIM = 0U;
    PWR_MGMT_CTRL  = 0U;
    OCP_CONFIG     = 0x0A500000U;
    IODFT_TLGC     = HW_RD_REG32(base_addr +
                                 EMIF_IODFT_TLGC);
    DLL_CALIB_CTRL    = 0x00050000U;
    ZQ_CONFIG         = 0U;
    TEMP_ALERT_CONFIG = HW_RD_REG32(base_addr +
                                    EMIF_TEMPERATURE_ALERT_CONFIG);
    RDWR_LVL_RMP_WIN = HW_RD_REG32(base_addr +
                                   EMIF_READ_WRITE_LEVELING_RAMP_WINDOW);

    DDR_PHY_CTRL_2 = HW_RD_REG32(base_addr +
                                 EMIF_DDR_PHY_CONTROL_2);
    PRI_COS_MAP      = 0U;
    CONNID_COS_1_MAP = 0U;
    CONNID_COS_2_MAP = 0U;
    RD_WR_EXEC_THRSH = 0x00000305U;
    COS_CONFIG       = 0x00FFFFFFU;

    /* EMIF_PHY_FIFO_WE_SLAVE_RATIO (RD_DQS_GATE) */
    temp           = 0x80U;
    EXT_PHY_CTRL_2 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_3 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_4 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_5 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_6 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_RD_DQS_SLAVE_RATIO */
    temp            = 0x40U;
    EXT_PHY_CTRL_7  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_8  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_9  = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_10 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_11 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DATA_SLAVE_RATIO */
    temp = 0x60U;
    EXT_PHY_CTRL_12 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_13 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_14 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_15 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_16 = (temp << 16U) | (temp << 0U);

    /* EMIF_PHY_WR_DQS_SLAVE_RATIO */
    temp = 0x30U;
    EXT_PHY_CTRL_17 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_18 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_19 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_20 = (temp << 16U) | (temp << 0U);
    EXT_PHY_CTRL_21 = (temp << 16U) | (temp << 0U);

    /* 26-36 are updated so that uninitialized variables are not used */
    /* EMIF_PHY_GATELVL_INIT_RATIO */
    EXT_PHY_CTRL_26 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_26);
    EXT_PHY_CTRL_27 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_27);
    EXT_PHY_CTRL_28 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_28);
    EXT_PHY_CTRL_29 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_29);
    EXT_PHY_CTRL_30 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_30);

    /* EMIF_PHY_WRLVL_INIT_RATIO */
    EXT_PHY_CTRL_31 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_31);
    EXT_PHY_CTRL_32 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_32);
    EXT_PHY_CTRL_33 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_33);
    EXT_PHY_CTRL_34 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_34);
    EXT_PHY_CTRL_35 = HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_35);

    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36);
    EXT_PHY_CTRL_36 = HW_RD_REG32(base_addr +
                                  EMIF_EXT_PHY_CONTROL_36_SHADOW);

    SDRAM_REF_CTRL = 0x20000618U;
    SDRAM_CONFIG_2 = 0U;
    SDRAM_CONFIG   = 0x43801A21U;

    DISABLE_READ_LEVELING      = 0U;
    DISABLE_READ_GATE_LEVELING = 0U;
    DISABLE_WRITE_LEVELING     = 0U;

    /* HW Leveling is not supported in DDR2 */
    HW_LEVELING_ENABLED = 0U;
}

static void TDA3xx_reset_emif_params_ddr2_333(uint32_t base_addr)
{
    TDA3xx_reset_emif_params_ddr2_400(base_addr);
}

static void TDA3xx_set_emif_params_ddr3_532(uint32_t base_addr)
{
    SDRAM_TIM_1 = 0xCEEF266BU;
#ifdef BOARD_TYPE_TDA3XX_RVP
    SDRAM_TIM_2 = 0x30BF7FDAU;
    SDRAM_TIM_3 = 0x427F8BA8U;
#else
    SDRAM_TIM_2 = 0x305A7FDAU;
    SDRAM_TIM_3 = 0x427F8558U;
#endif
    ZQ_CONFIG = 0x5007190BU;

    SDRAM_REF_CTRL_INIT = 0x000040F1U;
    SDRAM_REF_CTRL      = 0x00001035U;
#ifdef BOARD_TYPE_TDA3XX_RVP
    SDRAM_CONFIG = 0x61851BB2U;
#else
    SDRAM_CONFIG = 0x61811AB2U;
#endif
}

static void TDA3xx_set_emif_params_ddr3_400(uint32_t base_addr)
{
    EMIF_PHY_HALF_DELAY_MODE = 0x0U;

    SDRAM_TIM_1 = 0xCAAAD4DBU;
    SDRAM_TIM_2 = 0x20437FDAU;
    SDRAM_TIM_3 = 0x427F83F8U;
    ZQ_CONFIG   = 0x5007190BU;

    SDRAM_REF_CTRL_INIT = 0x000030D4U;
    SDRAM_REF_CTRL      = 0x00000C30U;
    SDRAM_CONFIG        = 0x618012B2U;
}

static void TDA3xx_set_emif_params_ddr3_333(uint32_t base_addr)
{
    EMIF_PHY_HALF_DELAY_MODE = 0x0U;
    EMIF_PHY_READ_LATENCY    = 0x9U;

    SDRAM_TIM_1 = 0xA888B41BU;
    SDRAM_TIM_2 = 0x20387FDAU;
    SDRAM_TIM_3 = 0x427F8358U;
    ZQ_CONFIG   = 0x5007190BU;

    SDRAM_REF_CTRL_INIT = 0x000028A6U;
    SDRAM_REF_CTRL      = 0x00000A25U;
    SDRAM_CONFIG        = 0x61800AB2U;
}

static void TDA3xx_set_emif_params_lpddr2_400(uint32_t base_addr)
{
    SDRAM_TIM_1 = 0x4EEB05E2U;
    SDRAM_TIM_2 = 0x20370DD2U;
    SDRAM_TIM_3 = 0x42B1C337U;
    ZQ_CONFIG   = 0x500B190BU;

    SDRAM_REF_CTRL_INIT = 0x800030D4U;
    /* for extended temp(>85C), refresh needs to be 4X faster!! */
    SDRAM_REF_CTRL = 0x00000C30U;
    SDRAM_CONFIG   = 0x83801A21U;
}

static void TDA3xx_set_emif_params_lpddr2_333(uint32_t base_addr)
{
    SDRAM_TIM_1           = 0x4AA8D4E2U;
    SDRAM_TIM_2           = 0x202E0B92U;
    SDRAM_TIM_3           = 0x428EA2B7U;
    ZQ_CONFIG             = 0x500B190BU;
    EMIF_PHY_READ_LATENCY = 0xBU;

    SDRAM_REF_CTRL_INIT = 0x800028A6U;
    /* For Normal Temp range (<85C) =>0x0000144AU; */
    /* For Extended temp range (>85C) =>0x00000289U; */
    SDRAM_REF_CTRL = 0x00000289U;
    SDRAM_CONFIG   = 0x83801A21U;
}

static void TDA3xx_set_emif_params_ddr2_400(uint32_t base_addr)
{
    EMIF_PHY_HALF_DELAY_MODE = 0U;
    EMIF_PHY_INVERT_CLKOUT   = 0U;

    SDRAM_TIM_1 = 0x6AAB15DAU;
    SDRAM_TIM_2 = 0x202D31D2U;
    SDRAM_TIM_3 = 0x5060029FU;
    ZQ_CONFIG   = 0U;

    SDRAM_REF_CTRL_INIT = 0x00001388U;
    SDRAM_REF_CTRL      = 0x20000618U;
    SDRAM_CONFIG        = 0x43801A21U;
}

static void TDA3xx_set_emif_params_ddr2_333(uint32_t base_addr)
{
    EMIF_PHY_HALF_DELAY_MODE = 0U;
    EMIF_PHY_INVERT_CLKOUT   = 0U;
    EMIF_PHY_READ_LATENCY    = 0x9U;

    SDRAM_TIM_1 = 0x6888E4DAU;
    SDRAM_TIM_2 = 0x202631D2U;
    SDRAM_TIM_3 = 0x5060022FU;
    ZQ_CONFIG   = 0U;

    SDRAM_REF_CTRL_INIT = 0x00001043U;
    SDRAM_REF_CTRL      = 0x20000512U;
    SDRAM_CONFIG        = 0x43801621U;
}

static void TDA3xx_CM_DDRIO_Config(uint32_t mode)
{
    /* DLL_OVERRIDE: No Override = 0; Override = 1
     * Value 1 is only for debug
     */
    HW_WR_REG32(SOC_CKGEN_CM_CORE_AON_BASE + CM_DLL_CTRL, 0);

    if (CFG_MODE_DDR3 == mode)
    {
        /* CTRL_CORE_CONTROL_DDRCACH1_0
         * - Impedance = 34ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_0
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_1
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_2
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCACH1_0,
                    0x80808080U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_0,
                    0x40404040U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_1,
                    0x40404040U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_2,
                    0x00404000U);

        /* CTRL_WKUP_EMIF1/2_SDRAM_CONFIG_EXT
         * - EMIF1_REG_PHY_NUM_OF_SAMPLES = 3
         * - EMIF1_REG_PHY_ALL_DQ_MPR_RD_RESP = 0
         * - EMIF1_PHY_RD_LOCAL_ODT = 60ohms
         * - Reset values for other fields.
         * - OK to set EMIF_ECC_EN set to 1 even if ECC feature is not used */
        if (1U == ENABLE_ECC)
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0001C127U); /* EMIF1_EN_ECC = 1 */
        }
        else
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0000C127U); /* EMIF1_EN_ECC = 0 */
        }
    }
    if (CFG_MODE_DDR2 == mode)
    {
        /* CTRL_CORE_CONTROL_DDRCACH1_0
         * - Impedance = 34ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_0
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_1
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_2
         * - Impedance = 40ohm / SlewRate = fastest / No pulls */
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCACH1_0,
                    0x80808080U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_0,
                    0x40404040U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_1,
                    0x40404040U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_2,
                    0x00404000U);

        /* CTRL_WKUP_EMIF1/2_SDRAM_CONFIG_EXT
         * - EMIF1_REG_PHY_NUM_OF_SAMPLES = 3
         * - EMIF1_REG_PHY_ALL_DQ_MPR_RD_RESP = 0
         * - EMIF1_PHY_RD_LOCAL_ODT = 60ohms
         * - Reset values for other fields.
         * - OK to set EMIF_ECC_EN set to 1 even if ECC feature is not used */
        if (1U == ENABLE_ECC)
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0001C127U); /* EMIF1_EN_ECC = 1 */
        }
        else
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0000C127U); /* EMIF1_EN_ECC = 0 */
        }
    }
    if (CFG_MODE_LPDDR2 == mode)
    {
        /* CTRL_CORE_CONTROL_DDRCACH1_0
         * - Impedance = RSVD / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_0
         * - Impedance = RSVD / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_1
         * - Impedance = RSVD / SlewRate = fastest / No pulls */
        /* CTRL_CORE_CONTROL_DDRCH1_2
         * - Impedance = RSVD / SlewRate = fastest / No pulls */
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCACH1_0,
                    0x48484848);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_0,
                    0x484A484A);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_1,
                    0x484A484A);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_DDRCH1_2,
                    0x004A4800U);

        /* CTRL_CORE_CONTROL_DDRIO_0
         * - DDRCH1_VREF_DQ0/1_INT_EN = 0, reset values for other fields */
        /* CTRL_CORE_CONTROL_DDRIO_0
         * - DDRCH2_VREF_DQ0/1_INT_EN = 0, reset values for other fields */
        HW_WR_REG32(0x4A002E50, 0x00018c60);

        /* CTRL_WKUP_EMIF1/2_SDRAM_CONFIG_EXT
         * - EMIF1_REG_PHY_NUM_OF_SAMPLES = 3
         * - EMIF1_REG_PHY_ALL_DQ_MPR_RD_RESP = 0
         * - EMIF1_PHY_RD_LOCAL_ODT = disabled
         * - Reset values for other fields.
         * - OK to set EMIF_ECC_EN set to 1 even if ECC feature is not used */
        if (1U == ENABLE_ECC)
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0001C127U); /* EMIF1_EN_ECC = 1 ODT = 60Ohms */
        }
        else
        {
            HW_WR_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                        CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT,
                        0x0000C127U); /* EMIF1_EN_ECC = 0 ODT=60Ohms */
        }
    }
}

static void EMIF_LPDDR2_Config(uint32_t base_addr)
{
/* TDA2X/TDA2EX do not support LPDDR2. Keeping this functions here to allow
 * easy maintenance and consistency of updates to DDR configuration routines
 * across TDA2X, TDA2EX and TDA3X platforms
 */
#if defined (SOC_TDA3XX)
    uint32_t temp;
    uint32_t siliconPackageType;
    uint32_t oppId;

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "--->>> Configuring LPDDR2 Device's MODE registers<<<---\n");

    /* EMIF_LPDDR2_MODE_REG_CFG */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000000U);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_DEBUG,
        "       Waiting for LPDDR2 Auto Initialization to be complete...\n");

    /* EMIF_LPDDR2_MODE_REG_DATA */
    while ((HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA) & 0x1U) != 0x0U)
    {
        /* Busy Loop */
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "       LPDDR2 Auto Initialization Process completed\n");

    /* EMIF_LPDDR2_MODE_REG_CFG: MR10 CS0 */
    /* EMIF_LPDDR2_MODE_REG_DATA: 0xFF => ZQ_Init, 0x56 => ZQCS,
     *                            0xAB => ZQCL,    0xC3 => ZQ reset */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x0000000AU);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA, 0xFFU);

    /* wait_for_1us */
    us_delay(1U);
    /* EMIF_LPDDR2_MODE_REG_CFG: MR1 CS0                  */
    /* EMIF_LPDDR2_MODE_REG_DATA: Burst length = 8, nWR=6 */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000001U);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA, 0x83U);

    /* EMIF_LPDDR2_MODE_REG_CFG: MR2 CS0                  */
    /* EMIF_LPDDR2_MODE_REG_DATA: RL6/WL3  for 400MHz     */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000002U);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA, 0x4U);

    siliconPackageType = SBLLibGetSiliconPackageType();
    /* Read the opp for which the SBL has been compiled */
    oppId = SBLGetOppId(siliconPackageType);

    SBLUtilsConfigDDRDpll(oppId);

    /* Poll for DLL lock status */
    while ((HW_RD_REG32(base_addr + EMIF_PHY_STATUS_1) & 0x1F3U) != 0x1F3U)
    {
        /* Wait for lock status */
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "--->>> PHY DLLs are locked...<<<---\n");

    /* Poll for PHY ready */
    while ((HW_RD_REG32(base_addr + EMIF_STATUS) & 0x4U) != 0x4U)
    {
        /* Wait for PHY ready */
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "--->>> PHY DLLs are Ready...<<<---\n");

    /* Enable Auto Refresh for the LPDDR memory */
    /* EMIF_LPDDR2_MODE_REG_CFG: MR2 CS0                  */
    /* EMIF_LPDDR2_MODE_REG_DATA: RL6/WL3  for 400MHz     */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x40000002U);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA, 0x4U);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_DEBUG,
        "--->>> Enabled Auto refresh. LPDDR2 Boot Up Init complete...<<<---\n");

    /* EMIF_LPDDR2_MODE_REG_CFG */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0U);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_DEBUG,
        "--->>> Reading back LPDDR2 ZQ initialization status......<<<---\n");
    temp = ((HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA)) >> 3U) & 0x3U;

    if (0U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "       LPDDR2 device does not support ZRQ Self test\n");
    }
    else if (1U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!RZQ Self test FAILED.!!!!\n");
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_DEBUG,
            "   !!!!ZQ Pin may be connected to VDDCA or is floating!!!!\n");
    }
    else if (2U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!RZQ Self test FAILED.!!!!\n");
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!ZQ Pin may be connected to Ground.!!!!\n");
    }
    else if (3U == temp)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_DEBUG,
            "       ZRQ Self test Complete. No Error condition Detected\n");
    }
    else
    {
        /* To Remove Misra C Error */
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 " ==============================================\n");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 " ==========  LPDDR2 Device Info      ==========\n");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 " ==============================================\n");

    /* Using EMIF_LPDDR2_MODE_REG_DATA and EMIF_LPDDR2_MODE_REG_CFG */
    /* Next three prints are disabled for C-compatibility */
    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000005U);

    temp = (HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA)) & 0xFFU;
    switch (temp) {
        case 0xFFU: /* Micron */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                         " ==========  Manufacturer ID= 0xFF   ==========\n");
            break;
        case 0x08U: /* Winbond */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                         " ==========  Manufacturer ID= 0x08   ==========\n");
            break;
        case 0x1BU: /* ISSI */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                         " ==========  Manufacturer ID= 0x1B   ==========\n");
            break;
        default:
            break;
    }

    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000008U);
    temp = ((HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA)) >> 2U) & 0xFU;
    if (0U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 64Mbit    ========\n");
    }
    else if (1U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 128Mbit   ========\n");
    }
    else if (2U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 256Mbit   ========\n");
    }
    else if (3U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 512Mbit   ========\n");
    }
    else if (4U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 1Gbit     ========\n");

        /*
         *  For 1 Gbit, no of SDRAM banks increased to 8.
         */
        SDRAM_CONFIG  = HW_RD_REG32(base_addr + EMIF_SDRAM_CONFIG);
        SDRAM_CONFIG &= (uint32_t) (~((uint32_t) 0x00000070U));
        SDRAM_CONFIG |= (uint32_t) (0x00000030U);
        HW_WR_REG32(base_addr + EMIF_SDRAM_CONFIG, SDRAM_CONFIG);
    }
    else if (5U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 2Gbit     ========\n");
    }
    else if (6U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 4Gbit     ========\n");
    }
    else if (7U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 8Gbit     ========\n");
    }
    else if (8U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 16Gbit    ========\n");
    }
    else if (9U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 Size     = 32Gbit    ========\n");
    }
    else
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  Unknown LPDDR2 Size!!       ========\n");
    }

    temp = ((HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA)) >> 6U) & 0x3U;

    if (0U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 IO Width = 32 bit    ========\n");
    }
    else if (1U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 IO Width = 16 bit    ========\n");
    }
    else if (2U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  LPDDR2 IO Width = 8 bit     ========\n");
    }
    else
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     " ========  Unknown IO Width !!!        ========\n");
    }
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 " ==============================================\n");

    HW_WR_REG32(base_addr + EMIF_LPDDR2_MODE_REG_CONFIG, 0x00000004U);

    temp = (HW_RD_REG32(base_addr + EMIF_LPDDR2_MODE_REG_DATA)) & 0x7U;

    if (0U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!LPDDR2 device low temp limit exceeded.!!!!\n");
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!Device may not function correctly.!!!!\n");
    }
    else if (7U == temp)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!LPDDR2 device high temp limit exceeded.!!!!\n");
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                     "   !!!!Device may not function correctly.!!!!\n");
    }
    else
    {
        /* To Remove Misra C Error */
    }
#endif
}

static void EMIF_DDR3_UpdateHWLevelOutput(uint32_t base_addr)
{
    /* Following function is needed for whenever CORE can go in and out of
     * INACTIVE/CSWR */
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "       Updating slave ratios in PHY_STATUSx registers\n");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG,
                 "       as per HW leveling output\n");

    if (0U == DISABLE_READ_GATE_LEVELING)
    {
        /* EMIF_PHY_FIFO_WE_SLAVE_RATIO (RD_DQS_GATE) */
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_2,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_12));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_2_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_12));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_3,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_13));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_3_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_13));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_4,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_14));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_4_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_14));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_5,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_15));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_5_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_15));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_6,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_16));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_6_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_16));
    }

    if (0U == DISABLE_READ_LEVELING)
    {
        /* EMIF_PHY_RD_DQS_SLAVE_RATIO */
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_7,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_7));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_7_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_7));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_8,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_8));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_8_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_8));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_9,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_9));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_9_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_9));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_10,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_10));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_10_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_10));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_11,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_11));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_11_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_11));
    }

    if (0U == DISABLE_WRITE_LEVELING)
    {
        /* EMIF_PHY_WR_DATA_SLAVE_RATIO */
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_12,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_17));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_12_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_17));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_13,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_18));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_13_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_18));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_14,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_19));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_14_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_19));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_15,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_20));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_15_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_20));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_16,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_21));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_16_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_21));

        /* EMIF_PHY_WR_DQS_SLAVE_RATIO */
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_17,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_22));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_17_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_22));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_18,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_23));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_18_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_23));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_19,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_24));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_19_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_24));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_20,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_25));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_20_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_25));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_21,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_26));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_21_SHADOW,
                    HW_RD_REG32(base_addr + EMIF_PHY_STATUS_26));
    }

    HW_WR_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1,
                (HW_RD_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1) |
                 EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_MASK |
                 EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_MASK |
                 EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_MASK));
    HW_WR_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1_SHADOW,
                (HW_RD_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1_SHADOW) |
                 EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_MASK |
                 EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_MASK |
                 EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_MASK));
    HW_WR_REG32(base_addr + EMIF_READ_WRITE_LEVELING_RAMP_CONTROL, 0U);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_DEBUG,
        "       HW leveling is now disabled. Using slave ratios from \n");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG, "       PHY_STATUSx registers\n");
}

static void EMIF_Config(uint32_t base_addr,
                        uint32_t mode,
                        uint32_t isHwLevelingEnabledInput,
                        uint32_t isEccEnabled)
{
    uint32_t EXT_PHY_CTRL_1;
    uint32_t DDR_PHY_CTRL_1;
    uint32_t EXT_PHY_CTRL_22;
    uint32_t EXT_PHY_CTRL_23;
    uint32_t EXT_PHY_CTRL_24;
    uint32_t EXT_PHY_CTRL_25;
    uint32_t RDWR_LVL_RMP_CTRL;
    uint32_t EMIF_PHY_LEVLELING_DISABLED;
    uint32_t isHwLevelingEnabled;

    if ((CFG_MODE_DDR2 == mode) || (CFG_MODE_LPDDR2 == mode))
    {
        /* Ignore function input when not using DDR3 */
        isHwLevelingEnabled = 0U;
    }
    else
    {
        isHwLevelingEnabled = isHwLevelingEnabledInput;
    }

    if ((1U == isHwLevelingEnabled) && (CFG_MODE_DDR3 == mode))
    {
        EMIF_PHY_LEVLELING_DISABLED = 0U;
        if (1U == DISABLE_READ_LEVELING)
        {
            EMIF_PHY_LEVLELING_DISABLED |=
                EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_MASK;
        }
        if (1U == DISABLE_READ_GATE_LEVELING)
        {
            EMIF_PHY_LEVLELING_DISABLED |=
                EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_MASK;
        }
        if (1U == DISABLE_WRITE_LEVELING)
        {
            EMIF_PHY_LEVLELING_DISABLED |=
                EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_MASK;
        }

        RDWR_LVL_RMP_CTRL =
            EMIF_READ_WRITE_LEVELING_RAMP_CONTROL_RDWRLVL_EN_MASK;
    }
    else
    {
        EMIF_PHY_LEVLELING_DISABLED =
            EMIF_DDR_PHY_CONTROL_1_WRLVL_MASK_MASK |
            EMIF_DDR_PHY_CONTROL_1_RDLVLGATE_MASK_MASK |
            EMIF_DDR_PHY_CONTROL_1_RDLVL_MASK_MASK;

        RDWR_LVL_RMP_CTRL = 0U;
    }

    DDR_PHY_CTRL_1 = (EMIF_PHY_READ_LATENCY << 0U) |
                     (EMIF_PHY_FAST_DLL_LOCK << 9U) |
                     (EMIF_PHY_DLL_LOCK_DIFF << 10U) |
                     (EMIF_PHY_INVERT_CLKOUT << 18U) |
                     (EMIF_PHY_DIS_CALIB_RST << 19U) |
                     (EMIF_PHY_HALF_DELAY_MODE << 21U) |
                     (EMIF_PHY_LEVLELING_DISABLED);
    EXT_PHY_CTRL_22 = (EMIF_PHY_FIFO_WE_IN_DELAY << 16U) |
                      (EMIF_PHY_CTRL_SLAVE_DELAY << 0U);
    EXT_PHY_CTRL_23 = (EMIF_PHY_WR_DQS_SLAVE_DELAY << 16U) |
                      (EMIF_PHY_RD_DQS_SLAVE_DELAY << 0U);
    EXT_PHY_CTRL_24 = (EMIF_PHY_DQ_OFFSET << 24U) |
                      (EMIF_PHY_GATELVL_INIT_MODE << 16U) |
                      (EMIF_PHY_USE_RANK0_DELAYS << 12U) |
                      (EMIF_PHY_WR_DATA_SLAVE_DELAY << 0U);
    EXT_PHY_CTRL_25 = (EMIF_PHY_DQ_OFFSET << 21U) |
                      (EMIF_PHY_DQ_OFFSET << 14U) |
                      (EMIF_PHY_DQ_OFFSET << 7U) |
                      (EMIF_PHY_DQ_OFFSET << 0U);

    /* Phy reset is required if you are coming back from a warm reset */
    HW_WR_REG32(base_addr + EMIF_IODFT_TLGC,
                HW_RD_REG32(base_addr + EMIF_IODFT_TLGC) | 0x400U);
    /* Wait for the PHY reset to complete */
    while ((HW_RD_REG32(base_addr + EMIF_IODFT_TLGC) & 0x400U) != 0U)
    {
        /* Wait */
    }

    if (1U == EMIF_PHY_INVERT_CLKOUT)
    {
        EXT_PHY_CTRL_1 = ((EMIF_PHY_CTRL_SLAVE_RATIO + 0x80U) << 20U) |
                         ((EMIF_PHY_CTRL_SLAVE_RATIO + 0x80U) << 10U) |
                         ((EMIF_PHY_CTRL_SLAVE_RATIO + 0x80U) << 0U);
    }
    else
    {
        EXT_PHY_CTRL_1 = (EMIF_PHY_CTRL_SLAVE_RATIO << 20U) |
                         (EMIF_PHY_CTRL_SLAVE_RATIO << 10U) |
                         (EMIF_PHY_CTRL_SLAVE_RATIO << 0U);
    }
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_1,
                EXT_PHY_CTRL_1);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_1_SHADOW,
                EXT_PHY_CTRL_1);

    if ((CFG_MODE_DDR3 == mode) ||
        (CFG_MODE_DDR2 == mode) ||
        (CFG_MODE_LPDDR2 == mode))
    {
        if (((1U == isHwLevelingEnabled) &&
             (1U == DISABLE_READ_GATE_LEVELING)) ||
            (0U == isHwLevelingEnabled))
        {
            /* EMIF_PHY_FIFO_WE_SLAVE_RATIO (RD_DQS_GATE) */
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_2,
                        EXT_PHY_CTRL_2);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_2_SHADOW,
                        EXT_PHY_CTRL_2);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_3,
                        EXT_PHY_CTRL_3);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_3_SHADOW,
                        EXT_PHY_CTRL_3);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_4,
                        EXT_PHY_CTRL_4);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_4_SHADOW,
                        EXT_PHY_CTRL_4);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_5,
                        EXT_PHY_CTRL_5);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_5_SHADOW,
                        EXT_PHY_CTRL_5);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_6,
                        EXT_PHY_CTRL_6);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_6_SHADOW,
                        EXT_PHY_CTRL_6);
        }

        if (((1U == isHwLevelingEnabled) &&
             (1U == DISABLE_READ_LEVELING)) ||
            (0U == isHwLevelingEnabled))
        {
            /* EMIF_PHY_RD_DQS_SLAVE_RATIO */
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_7,
                        EXT_PHY_CTRL_7);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_7_SHADOW,
                        EXT_PHY_CTRL_7);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_8,
                        EXT_PHY_CTRL_8);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_8_SHADOW,
                        EXT_PHY_CTRL_8);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_9,
                        EXT_PHY_CTRL_9);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_9_SHADOW,
                        EXT_PHY_CTRL_9);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_10,
                        EXT_PHY_CTRL_10);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_10_SHADOW,
                        EXT_PHY_CTRL_10);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_11,
                        EXT_PHY_CTRL_11);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_11_SHADOW,
                        EXT_PHY_CTRL_11);
        }

        if (((1U == isHwLevelingEnabled) &&
             (1U == DISABLE_WRITE_LEVELING)) ||
            (0U == isHwLevelingEnabled))
        {
            /* EMIF_PHY_WR_DATA_SLAVE_RATIO */
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_12,
                        EXT_PHY_CTRL_12);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_12_SHADOW,
                        EXT_PHY_CTRL_12);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_13,
                        EXT_PHY_CTRL_13);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_13_SHADOW,
                        EXT_PHY_CTRL_13);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_14,
                        EXT_PHY_CTRL_14);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_14_SHADOW,
                        EXT_PHY_CTRL_14);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_15,
                        EXT_PHY_CTRL_15);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_15_SHADOW,
                        EXT_PHY_CTRL_15);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_16,
                        EXT_PHY_CTRL_16);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_16_SHADOW,
                        EXT_PHY_CTRL_16);

            /* EMIF_PHY_WR_DQS_SLAVE_RATIO */
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_17,
                        EXT_PHY_CTRL_17);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_17_SHADOW,
                        EXT_PHY_CTRL_17);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_18,
                        EXT_PHY_CTRL_18);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_18_SHADOW,
                        EXT_PHY_CTRL_18);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_19,
                        EXT_PHY_CTRL_19);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_19_SHADOW,
                        EXT_PHY_CTRL_19);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_20,
                        EXT_PHY_CTRL_20);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_20_SHADOW,
                        EXT_PHY_CTRL_20);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_21,
                        EXT_PHY_CTRL_21);
            HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_21_SHADOW,
                        EXT_PHY_CTRL_21);
        }
    }

    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_22,
                EXT_PHY_CTRL_22);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_22_SHADOW,
                EXT_PHY_CTRL_22);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_23,
                EXT_PHY_CTRL_23);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_23_SHADOW,
                EXT_PHY_CTRL_23);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_24,
                EXT_PHY_CTRL_24);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_24_SHADOW,
                EXT_PHY_CTRL_24);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_25,
                EXT_PHY_CTRL_25);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_25_SHADOW,
                EXT_PHY_CTRL_25);

    if ((1U == isHwLevelingEnabled) && (CFG_MODE_DDR3 == mode))
    {
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_26,
                    EXT_PHY_CTRL_26);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_26_SHADOW,
                    EXT_PHY_CTRL_26);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_27,
                    EXT_PHY_CTRL_27);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_27_SHADOW,
                    EXT_PHY_CTRL_27);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_28,
                    EXT_PHY_CTRL_28);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_28_SHADOW,
                    EXT_PHY_CTRL_28);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_29,
                    EXT_PHY_CTRL_29);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_29_SHADOW,
                    EXT_PHY_CTRL_29);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_30,
                    EXT_PHY_CTRL_30);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_30_SHADOW,
                    EXT_PHY_CTRL_30);

        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_31,
                    EXT_PHY_CTRL_31);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_31_SHADOW,
                    EXT_PHY_CTRL_31);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_32,
                    EXT_PHY_CTRL_32);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_32_SHADOW,
                    EXT_PHY_CTRL_32);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_33,
                    EXT_PHY_CTRL_33);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_33_SHADOW,
                    EXT_PHY_CTRL_33);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_34,
                    EXT_PHY_CTRL_34);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_34_SHADOW,
                    EXT_PHY_CTRL_34);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_35,
                    EXT_PHY_CTRL_35);
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_35_SHADOW,
                    EXT_PHY_CTRL_35);
    }

    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36,
                EXT_PHY_CTRL_36);
    HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36_SHADOW,
                EXT_PHY_CTRL_36);

    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL_SHADOW,
                (EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_MASK |
                 SDRAM_REF_CTRL_INIT));
    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL,
                (EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_MASK |
                 SDRAM_REF_CTRL_INIT));

    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_1,
                SDRAM_TIM_1);
    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_1_SHADOW,
                SDRAM_TIM_1);
    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_2,
                SDRAM_TIM_2);
    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_2_SHADOW,
                SDRAM_TIM_2);
    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_3,
                SDRAM_TIM_3);
    HW_WR_REG32(base_addr + EMIF_SDRAM_TIMING_3_SHADOW,
                SDRAM_TIM_3);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_NVM_TIMING,
                LPDDR2_NVM_TIM);
    HW_WR_REG32(base_addr + EMIF_LPDDR2_NVM_TIMING_SHADOW,
                LPDDR2_NVM_TIM);
    HW_WR_REG32(base_addr + EMIF_POWER_MANAGEMENT_CONTROL,
                PWR_MGMT_CTRL);
    HW_WR_REG32(base_addr + EMIF_POWER_MANAGEMENT_CONTROL_SHADOW,
                PWR_MGMT_CTRL);
    HW_WR_REG32(base_addr + EMIF_OCP_CONFIG,
                OCP_CONFIG);
    HW_WR_REG32(base_addr + EMIF_IODFT_TLGC,
                IODFT_TLGC);
    HW_WR_REG32(base_addr + EMIF_DLL_CALIB_CTRL,
                DLL_CALIB_CTRL);
    HW_WR_REG32(base_addr + EMIF_DLL_CALIB_CTRL_SHADOW,
                DLL_CALIB_CTRL);
    HW_WR_REG32(base_addr + EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG,
                ZQ_CONFIG);
    HW_WR_REG32(base_addr + EMIF_TEMPERATURE_ALERT_CONFIG,
                TEMP_ALERT_CONFIG);
    HW_WR_REG32(base_addr + EMIF_READ_WRITE_LEVELING_RAMP_WINDOW,
                RDWR_LVL_RMP_WIN);
    HW_WR_REG32(base_addr + EMIF_READ_WRITE_LEVELING_RAMP_CONTROL,
                RDWR_LVL_RMP_CTRL);
    HW_WR_REG32(base_addr + EMIF_READ_WRITE_LEVELING_CONTROL,
                0U);

    HW_WR_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1,
                DDR_PHY_CTRL_1);
    HW_WR_REG32(base_addr + EMIF_DDR_PHY_CONTROL_1_SHADOW,
                DDR_PHY_CTRL_1);

    HW_WR_REG32(base_addr + EMIF_DDR_PHY_CONTROL_2,
                DDR_PHY_CTRL_2);
    HW_WR_REG32(base_addr + EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING,
                PRI_COS_MAP);
    HW_WR_REG32(base_addr + EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING,
                CONNID_COS_1_MAP);
    HW_WR_REG32(base_addr + EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING,
                CONNID_COS_2_MAP);
    HW_WR_REG32(base_addr + EMIF_READ_WRITE_EXECUTION_THRESHOLD,
                RD_WR_EXEC_THRSH);
    HW_WR_REG32(base_addr + EMIF_COS_CONFIG,
                COS_CONFIG);

    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL_SHADOW,
                SDRAM_REF_CTRL_INIT);
    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL,
                SDRAM_REF_CTRL_INIT);
    HW_WR_REG32(base_addr + EMIF_SDRAM_CONFIG_2,
                SDRAM_CONFIG_2);
    HW_WR_REG32(base_addr + EMIF_SDRAM_CONFIG,
                SDRAM_CONFIG);
    if (CFG_MODE_LPDDR2 != mode)
    {
        /* If delay is not present, interconnect can throw a false error */
        us_delay(1000U);
    }

    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL_SHADOW,
                SDRAM_REF_CTRL);
    HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL,
                SDRAM_REF_CTRL);

    if (CFG_MODE_LPDDR2 == mode)
    {
        HW_WR_REG32(base_addr + EMIF_SDRAM_CONFIG_2,
                    SDRAM_CONFIG_2);
        HW_WR_REG32(base_addr + EMIF_SDRAM_CONFIG,
                    SDRAM_CONFIG);
        EMIF_LPDDR2_Config(base_addr);
    }

    if ((1U == isHwLevelingEnabled) && (CFG_MODE_DDR3 == mode))
    {
        /* This is required for leveling of ECC macros */
        if ((1U == isEccEnabled) && (SOC_EMIF1_CONF_REGS_BASE == base_addr))
        {
            /* Configuration ensures ECC calculation does not happen */
            HW_WR_REG32(base_addr + EMIF_ECC_ADDRESS_RANGE_1,
                        0U);
            HW_WR_REG32(base_addr + EMIF_ECC_ADDRESS_RANGE_2,
                        0U);
            HW_WR_REG32(base_addr + EMIF_ECC_CTRL_REG,
                        (EMIF_ECC_CTRL_REG_REG_ECC_EN_MASK |
                         EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_PROT_MASK));
        }

        SBLLibPrintf(SBLLIB_TRACE_LEVEL_DEBUG, "       Launch full leveling\n");

        /* clear error status - FIFO_WE_IN_MISALIGNED */
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36,
                    (HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36) |
                     0x00000100U));
        HW_WR_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36_SHADOW,
                    (HW_RD_REG32(base_addr + EMIF_EXT_PHY_CONTROL_36_SHADOW) |
                     0x00000100U));

        /* Disable SDRAM refreshes before leveling */
        HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL,
                    (HW_RD_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL) |
                     EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_MASK));

        /* RDWR_LVL_CTRL - Launch full leveling */
        HW_WR_REG32(base_addr + EMIF_READ_WRITE_LEVELING_CONTROL,
                    EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLFULL_START_MASK);
        /* If delay is not present, interconnect can throw a false error */
        us_delay(300U);

        /* Wait for the leveling procedure to complete */
        while ((HW_RD_REG32(base_addr + EMIF_READ_WRITE_LEVELING_CONTROL) &
                EMIF_READ_WRITE_LEVELING_CONTROL_RDWRLVLFULL_START_MASK) !=
               0U)
        {
            /* Busy Loop */
        }

        /* Enable SDRAM refreshes after leveling */
        HW_WR_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL,
                    (HW_RD_REG32(base_addr + EMIF_SDRAM_REFRESH_CONTROL) &
                     ~EMIF_SDRAM_REFRESH_CONTROL_INITREF_DIS_MASK));

        if ((HW_RD_REG32(base_addr + EMIF_STATUS) & 0x70U) != 0U)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "ERROR: HW-Leveling time-out\n");
        }
        else
        {
            /* Following function is needed for whenever CORE can
             * go in and out of INACTIVE/CSWR */
            EMIF_DDR3_UpdateHWLevelOutput(base_addr);
        }

        /* This is done since ECC configuration is handled
         * in separate function */
        HW_WR_REG32(base_addr + EMIF_ECC_CTRL_REG, 0U);
    }
}

void SBLUtilsDDR3Config(uint32_t ddrSpeed)
{
    TDA3xx_CM_DDRIO_Config(CFG_MODE_DDR3);

    if ((uint32_t) SBLLIB_DDR_SPEED_532MHZ == ddrSpeed)
    {
        TDA3xx_reset_emif_params_ddr3_532(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_ddr3_532(SOC_EMIF1_CONF_REGS_BASE);
    }
    else if ((uint32_t) SBLLIB_DDR_SPEED_400MHZ == ddrSpeed)
    {
        TDA3xx_reset_emif_params_ddr3_400(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_ddr3_400(SOC_EMIF1_CONF_REGS_BASE);
    }
    else if ((uint32_t) SBLLIB_DDR_SPEED_333MHZ == ddrSpeed)
    {
        TDA3xx_reset_emif_params_ddr3_333(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_ddr3_333(SOC_EMIF1_CONF_REGS_BASE);
    }
    else
    {
        /* Should never enter here */
    }

    EMIF_Config(SOC_EMIF1_CONF_REGS_BASE,
                CFG_MODE_DDR3,
                HW_LEVELING_ENABLED,
                ENABLE_ECC);
}

void SBLUtilsDDR2Config(uint32_t ddrSpeed)
{
    TDA3xx_CM_DDRIO_Config(CFG_MODE_DDR2);

    if ((uint32_t) SBLLIB_DDR_SPEED_400MHZ == ddrSpeed)
    {
        TDA3xx_reset_emif_params_ddr2_400(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_ddr2_400(SOC_EMIF1_CONF_REGS_BASE);
    }
    else if ((uint32_t) SBLLIB_DDR_SPEED_333MHZ == ddrSpeed)
    {
        TDA3xx_reset_emif_params_ddr2_333(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_ddr2_333(SOC_EMIF1_CONF_REGS_BASE);
    }
    else
    {
        /* Should never enter here */
    }

    EMIF_Config(SOC_EMIF1_CONF_REGS_BASE,
                CFG_MODE_DDR2,
                HW_LEVELING_ENABLED,
                ENABLE_ECC);
}

void SBLUtilsLPDDR2Config(uint32_t lpddr2Speed)
{
    TDA3xx_CM_DDRIO_Config(CFG_MODE_LPDDR2);

    if ((uint32_t) SBLLIB_DDR_SPEED_400MHZ == lpddr2Speed)
    {
        TDA3xx_reset_emif_params_lpddr2_400(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_lpddr2_400(SOC_EMIF1_CONF_REGS_BASE);
    }
    else if ((uint32_t) SBLLIB_DDR_SPEED_333MHZ == lpddr2Speed)
    {
        TDA3xx_reset_emif_params_lpddr2_333(SOC_EMIF1_CONF_REGS_BASE);
        TDA3xx_set_emif_params_lpddr2_333(SOC_EMIF1_CONF_REGS_BASE);
    }
    else
    {
        /* Should never enter here */
    }

    EMIF_Config(SOC_EMIF1_CONF_REGS_BASE,
                CFG_MODE_LPDDR2,
                HW_LEVELING_ENABLED,
                ENABLE_ECC);
}

