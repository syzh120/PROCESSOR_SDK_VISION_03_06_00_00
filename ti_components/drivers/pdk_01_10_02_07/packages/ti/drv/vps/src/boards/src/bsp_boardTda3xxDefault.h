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
 *  \file bsp_boardTda3xxDefault.h
 *
 *  \brief Tda3xx default (base) board data.
 */

#ifndef BSP_BOARD_TDA3XX_DEFAULT_H_
#define BSP_BOARD_TDA3XX_DEFAULT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bsp_boardTda2exCalDev.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#ifdef VPS_VIP_BUILD

/* Below are the sensors connected to VIN1A */
#define VPS_CAPT_DRV_ID_TDA3XX_SII9127_0        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_ADV7611_0        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_DS90UH926_0      (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_OV1063X_0        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_0     (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_0     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_DS90UH926_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))

/* Below are the same sensors connected to VIN2A */
#define VPS_CAPT_DRV_ID_TDA3XX_SII9127_1        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_ADV7611_1        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_OV1063X_1        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_1     (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_1     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_1 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_1 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_1 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_1 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_1 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA3XX_SII9127_0                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_ADV7611_0                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_DS90UH926_0                  (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_OV1063X_0                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_0                 (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_0                 (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_SII9127_1                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_ADV7611_1                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_OV1063X_1                    (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_1                 (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_1                 (0U)

#define VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_0               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_0               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_DS90UH926_0             (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_0               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_0            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_0            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_1               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_1               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_1               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_1            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_1            (0U)
#endif


#ifdef VPS_CAL_BUILD

#define VPS_CAPT_DRV_ID_TDA3XX_OV10640_0         (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2 (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2_OTF    \
                                                 (VPS_CAPT_INST_ISS_CAL_A_OTF)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI  (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI_OTF \
                                                 (VPS_CAPT_INST_ISS_CAL_A_OTF)

#define VPS_CAPT_DRV_ID_TDA3XX_IMX224_0          (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_IMX224_CSI2  (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0  (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_2 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_3 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_0 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_1 \
    (VPS_CAPT_INST_ISS_CAL_A_OTF)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_2 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_3 \
    (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_4 \
    (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_5 \
    (VPS_CAPT_INST_ISS_CAL_A + 3U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_0 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_1 \
    (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_2 \
    (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_3 \
    (VPS_CAPT_INST_ISS_CAL_A + 3U)
#define VPS_CAPT_DRV_ID_TDA3XX_OV2775_0     (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV2775_CSI2   \
    (VPS_CAPT_INST_ISS_CAL_A)

#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0140_0     (FVID2_VPS_CAPT_VID_DRV)

#else

#define VPS_CAPT_DRV_ID_TDA3XX_OV10640_0                    (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2_OTF        (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI             (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI_OTF         (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_IMX224_0                     (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_IMX224_CSI2             (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0             (0U)

#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_2            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_3            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_0            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_1            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_2            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_3            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_4            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_5            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_0           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_1           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_2           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_3           (0U)
#define VPS_CAPT_DRV_ID_TDA3XX_OV2775_0                     (0U)
#define VPS_CAPT_DRV_INST_ID_TDA3XX_OV2775_CSI2             (0U)

#define VPS_CAPT_DRV_ID_TDA3XX_APT_AR0140_0                 (0U)

#endif

#ifdef VPS_DSS_BUILD

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_LCD           (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_LCD      (VPS_DSS_DISPC_OVLY_DPI1)

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_SII9022A_HDMI      (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_SII9022A_HDMI ( \
        VPS_DSS_DISPC_OVLY_DPI1)

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_DS90UH925        (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_DS90UH925   (VPS_DSS_DISPC_OVLY_DPI1)

#else

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_LCD           (0U)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_LCD      (0U)

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_SII9022A_HDMI      (0U)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_SII9022A_HDMI (0U)

#define VPS_DSS_DRV_ID_TDA3XX_DEFAULT_DS90UH925         (0U)
#define VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_DS90UH925    (0U)

#endif

#define BSP_BOARD_TDA3XX_DEFAULT_DEVDATA                                       \
    {                                                                          \
        {                                                                      \
            FVID2_LCD_CTRL_DRV,                         /* devDrvId */         \
            0U,                                         /* instId */           \
            BSP_DEVICE_I2C_INST_ID_0,                   /* i2cInstId */        \
            BOARD_TLC59108_I2C_ADDR_0,                  /* i2cAddr */          \
            VPS_DSS_DRV_ID_TDA3XX_DEFAULT_LCD,          /* drvId */            \
            VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_LCD,     /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_ENC_SII9022A_DRV,                       /* devDrvId */   \
            0U,                                               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_0,                         /* i2cInstId */  \
            BOARD_SIL9022_I2C_ADDR_1,                         /* i2cAddr */    \
            VPS_DSS_DRV_ID_TDA3XX_DEFAULT_SII9022A_HDMI,      /* drvId */      \
            VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_SII9022A_HDMI, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                     /* selectDev */  \
            NULL,                                             /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                    /* powerOnDev */ \
        },                                                                     \
        {                                                                      \
            FVID2_VID_ENC_DS90UH925_DRV,                      /* devDrvId */   \
            0U,                                               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_0,                         /* i2cInstId */  \
            BOARD_DS90UH925_I2C_ADDR_15,                      /* i2cAddr */    \
            VPS_DSS_DRV_ID_TDA3XX_DEFAULT_DS90UH925,          /* drvId */      \
            VPS_DSS_DRV_INST_ID_TDA3XX_DEFAULT_DS90UH925,     /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                     /* selectDev */  \
            NULL,                                             /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                    /* powerOnDev */ \
        },                                                                     \
        {                                                                      \
            FVID2_VID_DEC_SII9127_DRV,                  /* devDrvId */         \
            BSP_DEVICE_SII9127_INST_ID_0,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_SII9127_I2C_ADDR_1,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_SII9127_0,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_0,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_DEC_SII9127_DRV,                  /* devDrvId */         \
            BSP_DEVICE_SII9127_INST_ID_1,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_SII9127_I2C_ADDR_1,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_SII9127_1,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_SII9127_1,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_DEC_ADV7611_DRV,                  /* devDrvId */         \
            BSP_DEVICE_ADV7611_INST_ID_0,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_ADV7611_I2C_ADDR_0,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_ADV7611_0,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_0,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_DEC_ADV7611_DRV,                  /* devDrvId */         \
            BSP_DEVICE_ADV7611_INST_ID_1,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_ADV7611_I2C_ADDR_0,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_ADV7611_1,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_ADV7611_1,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_DEC_DS90UH926_DRV,                /* devDrvId */         \
            BSP_DEVICE_DS90UH926_INST_ID_0,             /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_DS90UH926_I2C_ADDR_0,                 /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_DS90UH926_0,         /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_DS90UH926_0,    /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV1063X_DRV,               /* devDrvId */         \
            BSP_DEVICE_OV1063X_INST_ID_0,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_OV1063x_I2C_ADDR_0,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_OV1063X_0,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_0,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV1063X_DRV,               /* devDrvId */         \
            BSP_DEVICE_OV1063X_INST_ID_1,               /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_OV1063x_I2C_ADDR_0,                   /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_OV1063X_1,           /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV1063X_1,      /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,            /* devDrvId */         \
            BSP_DEVICE_LI_OV1063X_INST_ID_0,            /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_LI_OV1063X_I2C_ADDR_0,                /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_0,        /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_0,   /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,            /* devDrvId */         \
            BSP_DEVICE_LI_OV1063X_INST_ID_1,            /* instId */           \
            BSP_DEVICE_I2C_INST_ID_1,                   /* i2cInstId */        \
            BOARD_LI_OV1063X_I2C_ADDR_0,                /* i2cAddr */          \
            VPS_CAPT_DRV_ID_TDA3XX_LI_OV1063X_1,        /* drvId */            \
            VPS_CAPT_DRV_INST_ID_TDA3XX_LI_OV1063X_1,   /* drvInstId */        \
            &Bsp_boardSelectDeviceTda3xx,               /* selectDev */        \
            NULL,                                       /* resetDev */         \
            &Bsp_boardPowerOnDeviceTda3xx,              /* powerOnDev */       \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0132_INST_ID_0,               /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_0,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_0,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0132_INST_ID_1,               /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_1,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_1,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0132_INST_ID_2_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_1,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_2,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0132_INST_ID_2_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0132_1,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0132_3,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0140_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0140_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0140_0,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_0,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_APT_AR0140_DRV,               /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_1_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_AR0140_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_APT_AR0140_0,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_1,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,     /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_0,         /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0,       /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_2,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,     /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_1,         /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0,       /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_3,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,     /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_2,         /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0,       /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_4,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,     /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_3,         /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_CAL_APT_AR0140_0,       /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_APT_AR0140_5,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV,         /* devDrvId */      \
            BSP_DEVICE_IMX224_INST_ID_0,                   /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_IMX224_I2C_ADDR_CSI2,                    /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_IMX224_0,               /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_IMX224_CSI2,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV10640_CSI2_DRV,             /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_OV10640_I2C_ADDR_CSI2,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV10640_CSI2_DRV,             /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_1,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_OV10640_I2C_ADDR_CSI2,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CSI2_OTF,  /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV10640_CPI_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_OV10640_I2C_ADDR_CPI,                    /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV10640_CPI_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_1,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_OV10640_I2C_ADDR_CPI,                    /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_CPI_OTF,   /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_0,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_0,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_1,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_1,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_2,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_2,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_3,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV10640_IMI_3,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                              \
        {                                                                      \
            FVID2_VID_SENSOR_OV2775_CSI2_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV2775_INST_ID_0,                   /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_OV2775_I2C_ADDR_CSI2,                    /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA3XX_OV2775_0,               /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA3XX_OV2775_CSI2,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                              \
        {                                                                      \
            BSP_DRV_ID_UART,                               /* devDrvId */      \
            BSP_DEVICE_UART_INST_ID_0,                     /* instId */        \
            NULL,                                          /* i2cInstId */     \
            NULL,                                          /* i2cAddr */       \
            NULL,                                          /* drvId */         \
            NULL,                                          /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            BSP_DRV_ID_UART,                               /* devDrvId */      \
            BSP_DEVICE_UART_INST_ID_1,                     /* instId */        \
            NULL,                                          /* i2cInstId */     \
            NULL,                                          /* i2cAddr */       \
            NULL,                                          /* drvId */         \
            NULL,                                          /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            BSP_DRV_ID_UART,                               /* devDrvId */      \
            BSP_DEVICE_UART_INST_ID_2,                     /* instId */        \
            NULL,                                          /* i2cInstId */     \
            NULL,                                          /* i2cAddr */       \
            NULL,                                          /* drvId */         \
            NULL,                                          /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            BSP_DRV_ID_MCSPI,                              /* devDrvId */      \
            BSP_DEVICE_MCSPI_INST_ID_0,                    /* instId */        \
            NULL,                                          /* i2cInstId */     \
            NULL,                                          /* i2cAddr */       \
            NULL,                                          /* drvId */         \
            NULL,                                          /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            BSP_DRV_ID_MMC,                                /* devDrvId */      \
            BSP_DEVICE_MMC_INST_ID_4,                      /* instId */        \
            NULL,                                          /* i2cInstId */     \
            NULL,                                          /* i2cAddr */       \
            NULL,                                          /* drvId */         \
            NULL,                                          /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,           /* devDrvId */      \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_UB960_OV1063X_1_ALIAS_I2C_ADDR,          /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_1,            /* drvInstId */     \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,           /* devDrvId */      \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_UB960_OV1063X_2_ALIAS_I2C_ADDR,          /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_2,            /* drvInstId */     \
            NULL,                                          /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,           /* devDrvId */      \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_UB960_OV1063X_3_ALIAS_I2C_ADDR,          /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_3,            /* drvInstId */     \
            NULL,                                          /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,           /* devDrvId */      \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_5,           /* instId */        \
            BSP_DEVICE_I2C_INST_ID_1,                      /* i2cInstId */     \
            BOARD_UB960_OV1063X_4_ALIAS_I2C_ADDR,          /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_OV10635X,           /* drvId */         \
            VPS_CAPT_DRV_INST_ID_CAL_OV10635_4,            /* drvInstId */     \
            NULL,                                          /* selectDev */     \
            NULL,                                          /* resetDev */      \
            NULL,                                          /* powerOnDev */    \
        },                                                                     \
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

#endif  /* #ifndef BSP_BOARD_TDA3XX_DEFAULT_H_ */

/* @} */
