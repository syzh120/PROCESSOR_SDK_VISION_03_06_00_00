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
 *  \file bsp_boardTda2exMultiDes.h
 *
 *  \brief TDA2EX Multi Deserialiser board data.
 *  In Multi deserializer board the camera inputs connects are shown below
 *   CAM2 ---> VIN1A
 *   CAM4 ---> VIN1B
 *   CAM1 ---> VIN2A
 *   CAM3 ---> VIN2B
 */

#ifndef BSP_BOARD_TDA2EX_MULTIDES_H_
#define BSP_BOARD_TDA2EX_MULTIDES_H_

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
 * !!!IMPORTANT!!! If redifining camera addresses they always have to be put
 * into consecutive order
 * (0x20 - CAMERA 1, 0x21 - CAMERA 2, 0x22 - CAMERA 3 etc.).
 * The following is not allowed: 0x20 - CAMERA 1, 0x22 - CAMERA 2, 0x21 - CAMERA
 * 3 etc.
 * These alias address should be in sync with what is defined in bsputils_app.c
 * file.
 */
#define BOARD_OV1063X_1_ALIAS_I2C_ADDR     (0x38U) /* 0x70/2 */
#define BOARD_OV1063X_2_ALIAS_I2C_ADDR     (0x39U) /* 0x72/2 */
#define BOARD_OV1063X_3_ALIAS_I2C_ADDR     (0x3AU) /* 0x74/2 */
#define BOARD_OV1063X_4_ALIAS_I2C_ADDR     (0x3BU) /* 0x76/2 */
#define BOARD_OV1063X_5_ALIAS_I2C_ADDR     (0x3CU) /* 0x78/2 */

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_1_TDA2EX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_2_TDA2EX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB))
#define VPS_CAPT_DRV_INST_ID_3_TDA2EX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_4_TDA2EX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB))

#else

#define VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X         (0U)

#define VPS_CAPT_DRV_INST_ID_1_TDA2EX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_2_TDA2EX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_3_TDA2EX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_4_TDA2EX_MULTIDES_OV1063X  (0U)
#endif

#define BSP_BOARD_TDA2EX_MULTIDES_DEVDATA_REVC                               \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_2_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_5,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_5_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_1,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_1_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_4_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_4_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
    }

#define BSP_BOARD_TDA2EX_MULTIDES_DEVDATA_REVA                               \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_2_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_4_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_1,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_1_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_OV1063X_3_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_4_TDA2EX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exMultiDes,           /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                  /* powerOnDev */ \
        },                                                                   \
    }

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

#endif  /* #ifndef BSP_BOARD_TDA2EX_MULTIDES_H_ */

/* @} */
