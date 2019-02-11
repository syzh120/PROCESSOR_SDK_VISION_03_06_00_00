/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file stw_board_priv.h
 *
 * \brief  This file contains module-private information for the board module.
 * It includes I2C slave addresses for all devices
 *
 */

#ifndef STW_BOARD_PRIV_H_
#define STW_BOARD_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/stw_lld/boards/stw_board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOARD_EEPROM_I2C_ADDR_0                 (0x50U)
#define BOARD_EEPROM_I2C_ADDR_1                 (0x51U)

/** \brief I2C address of the OmniVision 10630/10635 Sensor. */
#define BOARD_OV1063x_I2C_ADDR_0                (0x30U)
#define BOARD_IO_EXP_I2C_ADDR_0                 (0x20U)
#define BOARD_IO_EXP_I2C_ADDR_1                 (0x21U)
#define BOARD_IO_EXP_I2C_ADDR_2                 (0x22U)
#define BOARD_IO_EXP_I2C_ADDR_3                 (0x23U)
#define BOARD_IO_EXP_I2C_ADDR_4                 (0x24U)
#define BOARD_IO_EXP_I2C_ADDR_5                 (0x25U)
#define BOARD_IO_EXP_I2C_ADDR_6                 (0x26U)
#define BOARD_IO_EXP_I2C_ADDR_7                 (0x27U)

#define BOARD_SII9127_I2C_ADDR_1                (0x31U)

#define BOARD_TLC59108_I2C_ADDR_0               (0x40U)

/* THS7353 filter I2C address present in VC daughter card */
#define BOARD_THS7353_I2C_ADDR                  (0x2CU)

/** \brief I2C address of the PCA9543 i2c switch. */
#define BOARD_PCA9543_I2C_ADDR                  (0x70U)

#define BOARD_TEMP_SENSOR_I2C_ADDR              (0x48U)

#define BOARD_TVP5158_I2C_ADDR_0                (0x58U)
#define BOARD_TVP5158_I2C_ADDR_7                (0x5FU)

#define BOARD_SII9127_I2C_ADDR_0                (0x30U)

#define BOARD_TVP7002_I2C_ADDR_0                (0x5DU)

#define BOARD_SII9135_I2C_ADDR_0                (0x30U)

/* Defines specific to on-board peripherals */
#define PCF8575_P0_0_MASK                       (0x01U)
#define PCF8575_P0_1_MASK                       (0x02U)
#define PCF8575_P0_2_MASK                       (0x04U)
#define PCF8575_P0_3_MASK                       (0x08U)
#define PCF8575_P0_4_MASK                       (0x10U)
#define PCF8575_P0_5_MASK                       (0x20U)
#define PCF8575_P0_6_MASK                       (0x40U)
#define PCF8575_P0_7_MASK                       (0x80U)
#define PCF8575_P1_0_MASK                       (0x01U)
#define PCF8575_P1_1_MASK                       (0x02U)
#define PCF8575_P1_2_MASK                       (0x04U)
#define PCF8575_P1_3_MASK                       (0x08U)
#define PCF8575_P1_4_MASK                       (0x10U)
#define PCF8575_P1_5_MASK                       (0x20U)
#define PCF8575_P1_6_MASK                       (0x40U)
#define PCF8575_P1_7_MASK                       (0x80U)

#define TCA64_P0_0_MASK                         (0x01U)
#define TCA64_P0_1_MASK                         (0x02U)
#define TCA64_P0_2_MASK                         (0x04U)
#define TCA64_P0_3_MASK                         (0x08U)
#define TCA64_P0_4_MASK                         (0x10U)
#define TCA64_P0_5_MASK                         (0x20U)
#define TCA64_P0_6_MASK                         (0x40U)
#define TCA64_P0_7_MASK                         (0x80U)
#define TCA64_P1_0_MASK                         (0x01U)
#define TCA64_P1_1_MASK                         (0x02U)
#define TCA64_P1_2_MASK                         (0x04U)
#define TCA64_P1_3_MASK                         (0x08U)
#define TCA64_P1_4_MASK                         (0x10U)
#define TCA64_P1_5_MASK                         (0x20U)
#define TCA64_P1_6_MASK                         (0x40U)
#define TCA64_P1_7_MASK                         (0x80U)
#define TCA64_P2_0_MASK                         (0x01U)
#define TCA64_P2_1_MASK                         (0x02U)
#define TCA64_P2_2_MASK                         (0x04U)
#define TCA64_P2_3_MASK                         (0x08U)
#define TCA64_P2_4_MASK                         (0x10U)
#define TCA64_P2_5_MASK                         (0x20U)
#define TCA64_P2_6_MASK                         (0x40U)
#define TCA64_P2_7_MASK                         (0x80U)

/*  VC
 *  PCF8575 - mappings
 *  P16, P17 - TVP7002 select
 *  P7 - THS73861_FILTER2
 *  P6 - THS73861_FILTER1
 *  P5 - THS73861_BYPASS
 *  P4 - THS73861_DISABLE
 *  P0 - TVP7002_RSTN
 */
#define BOARD_PCF8575_TVP_RESETn_MASK           (PCF8575_P0_0_MASK)
#define BOARD_PCF8575_THS73861_DISABLE_MASK     (PCF8575_P0_4_MASK)
#define BOARD_PCF8575_THS73861_BYPASS_MASK      (PCF8575_P0_5_MASK)
#define BOARD_PCF8575_THS73861_FILTER1_MASK     (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_THS73861_FILTER2_MASK     (PCF8575_P0_7_MASK)
#define BOARD_PCF8575_SEL_TVP_S0_MASK           (PCF8575_P1_6_MASK)

/*Pad config constant values */
#define BOARD_PULLUDENABLE_ENABLE         (0U)
#define BOARD_PULLUDENABLE_DISABLE        (1U)
#define BOARD_PULLTYPESELECT_PULL_UP      (1U)
#define BOARD_PULLTYPESELECT_PULL_DOWN    (0U)
#define BOARD_INPUTENABLE_ENABLE          (1U)
#define BOARD_INPUTENABLE_DISABLE         (0U)
#define BOARD_SLEWCONTROL_FAST_SLEW       (0U)
#define BOARD_SLEWCONTROL_SLOW_SLEW       (1U)
#define BOARD_WAKEUPENABLE_ENABLE         (1U)
#define BOARD_WAKEUPENABLE_DISABLE        (0U)
#define BOARD_DEFAULT                     (0xFFU)

#define BOARD_PRCM_MODULEMODE_ENABLE           (2U)
#define BOARD_PRCM_MODULEMODE_MASK             (3U)

/** \brief Invalid pin number */
#define BOARD_PINMUX_INVALID_PIN            (-1)

#define BOARD_PAD_MUXMODE_SHIFT                  (0U)
#define BOARD_PAD_MUXMODE_MASK                   (0x0000000fU)
#define BOARD_PAD_WAKEUPEVENT_SHIFT              (25U)
#define BOARD_PAD_WAKEUPEVENT_MASK               (0x02000000U)
#define BOARD_PAD_WAKEUPENABLE_SHIFT             (24U)
#define BOARD_PAD_WAKEUPENABLE_MASK              (0x01000000U)
#define BOARD_PAD_SLEWCONTROL_SHIFT              (19U)
#define BOARD_PAD_SLEWCONTROL_MASK               (0x00080000U)
#define BOARD_PAD_INPUTENABLE_SHIFT              (18U)
#define BOARD_PAD_INPUTENABLE_MASK               (0x00040000U)
#define BOARD_PAD_PULLTYPESELECT_SHIFT           (17U)
#define BOARD_PAD_PULLTYPESELECT_MASK            (0x00020000U)
#define BOARD_PAD_PULLUDENABLE_SHIFT             (16U)
#define BOARD_PAD_PULLUDENABLE_MASK              (0x00010000U)

#define NUM_OF_TDA2XXBOARD_PINMUX_CONFIGUARATIONS       (69)
#define NUM_OF_TDA2EXBOARD_PINMUX_CONFIGUARATIONS       (97)
#define NUM_OF_TDA3XXBOARD_PINMUX_CONFIGUARATIONS       (57)

/**
 *  \brief Board MMR Region ID.
 */
typedef enum
{
    BOARD_MMR_REGION_1 = 0x0000U,
    /**< Board MMR region 1  */
    BOARD_MMR_REGION_2,
    /**< Board MMR region 2  */
    BOARD_MMR_REGION_3,
    /**< Board MMR region 3  */
    BOARD_MMR_REGION_4,
    /**< Board MMR region 4  */
    BOARD_MMR_REGION_5
    /**< Board MMR region 5  */
} boardMMRRegion_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct boardCommonObj
{
    boardId_t          boardId;
    /**< Board ID. For valid values see #boardId_t. */
    boardRev_t         baseBoardRev;
    /**< Base Board revision. */
    boardRev_t         dcBoardRev;
    /**< Daughter card board revision. */
    boardCustomData_t *customData;
    /**< Pointer to custom board data structure. */
} boardCommonObj_t;

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

int32_t BOARDTI814xInit(boardInitParams_t *pInitPrms);

int32_t BOARDTda2xxInit(const boardInitParams_t *pInitPrms);
boardId_t BOARDGetIdTda2xx(void);
boardRev_t BOARDGetBaseBoardRevTda2xx(void);
boardRev_t BOARDGetDcRevTda2xx(void);
const boardI2cData_t *BOARDGetI2cDataTda2xx(void);
const boardData_t *BOARDGetDataTda2xx(void);

int32_t BOARDTda3xxInit(const boardInitParams_t *pInitPrms);
boardId_t BOARDGetIdTda3xx(void);
boardRev_t BOARDGetBaseBoardRevTda3xx(void);
boardRev_t BOARDGetDcRevTda3xx(void);
const boardI2cData_t *BOARDGetI2cDataTda3xx(void);
const boardData_t *BOARDGetDataTda3xx(void);

boardId_t BOARDGetIdTI814x(void);
boardRev_t BOARDGetBaseBoardRevTI814x(void);
boardRev_t BOARDGetDcRevTI814x(void);
const boardI2cData_t *BOARDGetI2cDataTI814x(void);
const boardData_t *BOARDGetDataTI814x(void);

int32_t BOARDSelectModeTda3xx(uint32_t    devDrvId,
                              uint32_t    instId,
                              boardMode_t boardMod);
void BOARDTda2xxConfigConsolePinMux(uint32_t uartInstId);
void BOARDTda3xxConfigConsolePinMux(uint32_t uartInstId);
void BOARDTda2exConfigConsolePinMux(uint32_t uartInstId);

int32_t BOARDTda2exInit(const boardInitParams_t *pInitPrms);
boardId_t BOARDGetIdTda2ex(void);
boardRev_t BOARDGetBaseBoardRevTda2ex(void);
boardRev_t BOARDGetDcRevTda2ex(void);
const boardI2cData_t *BOARDGetI2cDataTda2ex(void);
const boardData_t *BOARDGetDataTda2ex(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef STW_BOARD_PRIV_H_ */

/* @} */
