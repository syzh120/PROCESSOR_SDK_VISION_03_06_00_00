/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *  \file bsp_boardTda2exCalDev.h
 *
 *  \brief TDA2EX UB960 EVM on CSI2 interface
 */

#ifndef BSP_BOARD_TDA2EX_CAL_DEVICES_H_
#define BSP_BOARD_TDA2EX_CAL_DEVICES_H_

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

/*
 * Cameras(OVSENSOR) addresses
 * These adresses are "Match" addresses used for addressing target camera at
 * deserializer's side.
 * The real camera address "CAMERA_ID_ADDR"is 0x30 (0x60/2) and it is the same
 * for all cameras
 * These alias address should be in sync with what is defined in
 * bsputils_ub960.c file variable gUb960Cfg_SAT0088_OV10635.
 * Please refer SAT0088_OV10635_PORT_X_SENSOR_ALIAS_ADDR in file 
 *                                          \examples\utility\bsputils_ub960.h
 * 
 */
#define BOARD_UB960_OV1063X_1_ALIAS_I2C_ADDR    (0x38U) /* 0x70/2 */
#define BOARD_UB960_OV1063X_2_ALIAS_I2C_ADDR    (0x39U) /* 0x72/2 */
#define BOARD_UB960_OV1063X_3_ALIAS_I2C_ADDR    (0x3AU) /* 0x74/2 */
#define BOARD_UB960_OV1063X_4_ALIAS_I2C_ADDR    (0x3BU) /* 0x76/2 */

#ifdef VPS_CAL_BUILD

#define VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X     (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_1      (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_2      (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_3      (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_4      (VPS_CAPT_INST_ISS_CAL_A + 3U)

#else /* VPS_CAL_BUILD */

#define VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X     (0U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_1      (0U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_2      (0U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_3      (0U)
#define VPS_CAPT_DRV_INST_ID_CAL_OV10635_4      (0U)

#endif /* VPS_CAL_BUILD */

/*  1. Nothing much to select the device,
    2. Reset/power is controlled by an GPIO of the serializer, hence UB960
        utility take care of this.
    3. Same as above for the power on
    */

#ifdef VPS_CAL_BUILD
#define BSP_BOARD_TDA2EX_CAL_UB960_OV10635_DEVDATA                           \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_UB960_OV1063X_1_ALIAS_I2C_ADDR,           /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_1,             /* drvInstId */  \
            NULL,                                           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            NULL,                                           /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_UB960_OV1063X_2_ALIAS_I2C_ADDR,           /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_2,             /* drvInstId */  \
            NULL,                                           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            NULL,                                           /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_UB960_OV1063X_3_ALIAS_I2C_ADDR,           /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_3,             /* drvInstId */  \
            NULL,                                           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            NULL,                                           /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_5,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_UB960_OV1063X_4_ALIAS_I2C_ADDR,           /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_4,             /* drvInstId */  \
            NULL,                                           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            NULL,                                           /* powerOnDev */ \
        },                                                                   \
    }

#else /* Just one dummy entry */

#define BSP_BOARD_TDA2EX_CAL_UB960_OV10635_DEVDATA                           \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_UB960_OV1063X_1_ALIAS_I2C_ADDR,           /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_1,             /* drvInstId */  \
            NULL,                                           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            NULL,                                           /* powerOnDev */ \
        },                                                                   \
    }
#endif /* VPS_CAL_BUILD */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_BOARD_TDA2EX_CAL_DEVICES_H_ */

/* @} */
