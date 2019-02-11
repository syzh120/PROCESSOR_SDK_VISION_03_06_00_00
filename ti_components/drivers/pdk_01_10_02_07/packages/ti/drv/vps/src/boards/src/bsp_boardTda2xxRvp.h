/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bsp_boardTda2xxRvp.h
 *
 *  \brief Tda2xx RVP 8 Channel board data.
 *
 */

#ifndef BSP_BOARD_TDA2XX_RVP_H_
#define BSP_BOARD_TDA2XX_RVP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define KID_FAIL                            (0xFF)

/* RVP board I2C addresses */
#define KTCA9539_U28_I2CADDR                (0x75U)
#define KTCA9539_U28_I2CBUS                 BSP_DEVICE_I2C_INST_ID_0

#define KTCA9539_U32_I2CADDR                (0x74U)
#define KTCA9539_U32_I2CBUS                 BSP_DEVICE_I2C_INST_ID_3

#define KTCA9539_U33_I2CADDR                (0x76U)
#define KTCA9539_U33_I2CBUS                 BSP_DEVICE_I2C_INST_ID_3

#define KTCA9539_U34_I2CADDR                (0x74U)
#define KTCA9539_U34_I2CBUS                 BSP_DEVICE_I2C_INST_ID_4

#define KTCA9539_I2CADDR_BASEBOARD          (0x75U)
#define KTCA9539_I2CADDR_BASEBOARD_REV1     (0x76U)
#define KTCA9539_I2CADDR_SOM                (0x74U)


#define BOARD_RVP_OV1063X_1_ALIAS_I2C_ADDR  (0x64U)
#define BOARD_RVP_OV1063X_2_ALIAS_I2C_ADDR  (0x65U)
#define BOARD_RVP_OV1063X_3_ALIAS_I2C_ADDR  (0x66U)
#define BOARD_RVP_OV1063X_4_ALIAS_I2C_ADDR  (0x67U)
#define BOARD_RVP_OV1063X_5_ALIAS_I2C_ADDR  (0x64U)
#define BOARD_RVP_OV1063X_6_ALIAS_I2C_ADDR  (0x65U)
#define BOARD_RVP_OV1063X_7_ALIAS_I2C_ADDR  (0x66U)
#define BOARD_RVP_OV1063X_8_ALIAS_I2C_ADDR  (0x67U)

#define BOARD_RVP_OV490_1_ALIAS_I2C_ADDR  (0x68U)
#define BOARD_RVP_OV490_2_ALIAS_I2C_ADDR  (0x69U)
#define BOARD_RVP_OV490_3_ALIAS_I2C_ADDR  (0x6AU)
#define BOARD_RVP_OV490_4_ALIAS_I2C_ADDR  (0x6BU)
#define BOARD_RVP_OV490_5_ALIAS_I2C_ADDR  (0x68U)
#define BOARD_RVP_OV490_6_ALIAS_I2C_ADDR  (0x69U)
#define BOARD_RVP_OV490_7_ALIAS_I2C_ADDR  (0x6AU)
#define BOARD_RVP_OV490_8_ALIAS_I2C_ADDR  (0x6BU)

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_1_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_2_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_3_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_4_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_5_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_6_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_7_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB))
#define VPS_CAPT_DRV_INST_ID_8_TDA2XX_RVP_CAMERA \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB))

#else

#define VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA         (0)

#define VPS_CAPT_DRV_INST_ID_1_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_2_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_3_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_4_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_5_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_6_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_7_TDA2XX_RVP_CAMERA (0)
#define VPS_CAPT_DRV_INST_ID_8_TDA2XX_RVP_CAMERA (0)

#endif

#define BSP_BOARD_TDA2XX_RVP_DEVDATA                                         \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_1,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_1_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_2_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_3_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_4_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_4_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_5,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_5_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_5_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_6,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_6_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_6_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_7,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_7_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_7_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_8,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV1063X_8_ALIAS_I2C_ADDR,             /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_8_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_1,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV490_1_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_2,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV490_2_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_3,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV490_3_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_4,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_3,                       /* i2cInstId */  \
            BOARD_RVP_OV490_4_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_4_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_5,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV490_5_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_5_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_6,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV490_6_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_6_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_7,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV490_7_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_7_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV490_DRV,              /* devDrvId */   \
            BSP_DEVICE_MULDES_OV490_INST_ID_8,              /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                       /* i2cInstId */  \
            BOARD_RVP_OV490_8_ALIAS_I2C_ADDR,               /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_RVP_CAMERA,              /* drvId */      \
            VPS_CAPT_DRV_INST_ID_8_TDA2XX_RVP_CAMERA,       /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxRVP,                /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xxRVP,               /* powerOnDev */ \
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

#endif  /* #ifndef BSP_BOARD_TDA2XX_RVP_H_ */

/* @} */
