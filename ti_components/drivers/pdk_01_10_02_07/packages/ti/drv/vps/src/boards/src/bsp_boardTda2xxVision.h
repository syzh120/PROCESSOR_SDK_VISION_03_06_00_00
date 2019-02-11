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
 *  \file bsp_boardTda2xxVision.h
 *
 *  \brief TDA2XX Vision board data.
 */

#ifndef BSP_BOARD_TDA2XX_VISION_H_
#define BSP_BOARD_TDA2XX_VISION_H_

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

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TDA2XX_VISION_SII9127           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_ADV7611           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_OV1063X           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_LI_OV1063X        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_APT_AR0132        (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_SII9127 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_ADV7611 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_LI_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_APT_AR0132 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2XX_VISION_SII9127           (0U)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_ADV7611           (0U)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_OV1063X           (0U)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_LI_OV1063X        (0U)
#define VPS_CAPT_DRV_ID_TDA2XX_VISION_APT_AR0132        (0U)

#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_SII9127      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_ADV7611      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_OV1063X      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_LI_OV1063X   (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_APT_AR0132   (0U)

#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)

/* I2C is connected to I2C2 in case of TI814x interposer */
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_SII9127  (BSP_DEVICE_I2C_INST_ID_2)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_ADV7611  (BSP_DEVICE_I2C_INST_ID_2)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_OV1063X  (BSP_DEVICE_I2C_INST_ID_2)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_LI_OV1063X      (BSP_DEVICE_I2C_INST_ID_1)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_APT_AR0132      (BSP_DEVICE_I2C_INST_ID_1)

#elif defined (SOC_TDA2PX)

#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_SII9127  (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_ADV7611  (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_OV1063X  (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_LI_OV1063X      (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_APT_AR0132      (BSP_DEVICE_I2C_INST_ID_4)

#else

#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_SII9127  (BSP_DEVICE_I2C_INST_ID_1)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_ADV7611  (BSP_DEVICE_I2C_INST_ID_1)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_OV1063X  (BSP_DEVICE_I2C_INST_ID_1)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_LI_OV1063X      (BSP_DEVICE_I2C_INST_ID_1)
#define BSP_DEVICE_I2C_INST_ID_TDA2XX_APT_AR0132      (BSP_DEVICE_I2C_INST_ID_1)

#endif

#define BSP_BOARD_TDA2XX_VISION_DEVDATA                                     \
    {                                                                       \
        {                                                                   \
            FVID2_VID_DEC_SII9127_DRV,                    /* devDrvId */    \
            0U,                                           /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_SII9127, /* i2cInstId */   \
            BOARD_SII9127_I2C_ADDR_1,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2XX_VISION_SII9127,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_SII9127,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xxVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            NULL,                                         /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_DEC_ADV7611_DRV,                    /* devDrvId */    \
            BSP_DEVICE_ADV7611_INST_ID_0,                 /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_ADV7611, /* i2cInstId */   \
            BOARD_ADV7611_I2C_ADDR_0,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2XX_VISION_ADV7611,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_ADV7611,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xxVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            NULL,                                         /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_OV1063X_DRV,                 /* devDrvId */    \
            0U,                                           /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2XX_VISION_OV1063X, /* i2cInstId */   \
            BOARD_OV1063x_I2C_ADDR_0,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2XX_VISION_OV1063X,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_OV1063X,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xxVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            &Bsp_boardPowerOnDeviceTda2xx,                /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,               /* devDrvId */   \
            BSP_DEVICE_LI_OV1063X_INST_ID_1,               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_TDA2XX_LI_OV1063X,      /* i2cInstId */  \
            BOARD_LI_OV1063X_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_VISION_LI_OV1063X,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_LI_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxVision,            /* selectDev */  \
            NULL,                                          /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */   \
            BSP_DEVICE_APT_AR0132_INST_ID_0,               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_TDA2XX_APT_AR0132,      /* i2cInstId */  \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_VISION_APT_AR0132,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2XX_VISION_APT_AR0132, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxVision,            /* selectDev */  \
            NULL,                                          /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */ \
        },                                                                  \
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

#endif  /* #ifndef BSP_BOARD_TDA2XX_VISION_H_ */

/* @} */
