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
 *  \file bsp_boardTda2pxDefault.h
 *
 *  \brief Tda2px Default board data.
 */

#ifndef BSP_BOARD_TDA2PX_DEFAULT_H_
#define BSP_BOARD_TDA2PX_DEFAULT_H_

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

#define VPS_CAPT_DRV_ID_TDA2PX_DEFAULT_LI_OV1063X       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_DEFAULT_LI_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))

#if defined (SOC_TDA2PX)
#define VPS_CAPT_DRV_LI_OV1063X_I2C_INST_ID         (BSP_DEVICE_I2C_INST_ID_4)
#else
#define VPS_CAPT_DRV_LI_OV1063X_I2C_INST_ID         (BSP_DEVICE_I2C_INST_ID_1)
#endif


#else

#define VPS_CAPT_DRV_ID_TDA2PX_DEFAULT_LI_OV1063X       (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_DEFAULT_LI_OV1063X  (0U)
#define VPS_CAPT_DRV_LI_OV1063X_I2C_INST_ID             (0U)

#endif

#ifdef VPS_DSS_BUILD

#define VPS_DSS_DRV_ID_TDA2PX_DEFAULT_LCD           (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA2PX_DEFAULT_LCD      (VPS_DSS_DISPC_OVLY_DPI1)

#if defined (SOC_TDA2PX)
#define VPS_DSS_DRV_DISP_I2C_INST_ID                (BSP_DEVICE_I2C_INST_ID_2)
#else
#define VPS_DSS_DRV_DISP_I2C_INST_ID                (BSP_DEVICE_I2C_INST_ID_0)
#endif

#else

#define VPS_DSS_DRV_ID_TDA2PX_DEFAULT_LCD           (0U)
#define VPS_DSS_DRV_INST_ID_TDA2PX_DEFAULT_LCD      (0U)
#define VPS_DSS_DRV_DISP_I2C_INST_ID                (0U)

#endif

#ifdef VPS_CAL_BUILD

#define VPS_CAPT_DRV_ID_TDA2PX_OV10640_0         (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2PX_OV10640_0         (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2PX_OV2775_0          (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_CSI2 (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV2775_CSI2  (VPS_CAPT_INST_ISS_CAL_A)

#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_0 \
    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_1 \
    (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_2 \
    (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_3 \
    (VPS_CAPT_INST_ISS_CAL_A + 3U)

#else

#define VPS_CAPT_DRV_ID_TDA2PX_OV10640_0         (0U)
#define VPS_CAPT_DRV_ID_TDA2PX_OV10640_0                    (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_CSI2            (0U)

#define VPS_CAPT_DRV_ID_TDA2PX_OV2775_0                    (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV2775_CSI2            (0U)

#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_0           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_1           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_2           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_3           (0U)

#endif


#define BSP_BOARD_TDA2PX_DEFAULT_DEVDATA                                     \
    {                                                                        \
        {                                                                    \
            FVID2_LCD_CTRL_DRV,                     /* devDrvId */           \
            0U,                                     /* instId */             \
            VPS_DSS_DRV_DISP_I2C_INST_ID,           /* i2cInstId */          \
            BOARD_TLC59108_I2C_ADDR_0,              /* i2cAddr */            \
            VPS_DSS_DRV_ID_TDA2PX_DEFAULT_LCD,      /* drvId */              \
            VPS_DSS_DRV_INST_ID_TDA2PX_DEFAULT_LCD, /* drvInstId */          \
            NULL,                                   /* selectDev */          \
            NULL,                                   /* resetDev */           \
            &Bsp_boardPowerOnDeviceTda2xx,          /* powerOnDev */         \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,                /* devDrvId */   \
            BSP_DEVICE_LI_OV1063X_INST_ID_0,                /* instId */     \
            VPS_CAPT_DRV_LI_OV1063X_I2C_INST_ID,            /* i2cInstId */  \
            BOARD_LI_OV1063X_I2C_ADDR_0,                    /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2PX_DEFAULT_LI_OV1063X,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2PX_DEFAULT_LI_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_0,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_1,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_2,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_MCSPI,                              /* devDrvId */    \
            BSP_DEVICE_MCSPI_INST_ID_1,                    /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_MMC,                                /* devDrvId */    \
            BSP_DEVICE_MMC_INST_ID_1,                      /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_MMC,                                /* devDrvId */    \
            BSP_DEVICE_MMC_INST_ID_2,                      /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                      \
            FVID2_VID_SENSOR_OV10640_CSI2_DRV,             /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_OV10640_I2C_ADDR_CSI2,                   /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_CSI2,      /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_OV2775_CSI2_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV2775_INST_ID_0,                   /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_OV2775_I2C_ADDR_CSI2,                    /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV2775_0,               /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV2775_CSI2,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                              \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_0,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_0,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_1,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_1,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_2,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_2,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                                     \
        {                                                                      \
            FVID2_VID_SENSOR_IMI_OV10640_DRV,              /* devDrvId */      \
            BSP_DEVICE_OV10640_INST_ID_0,                  /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */     \
            BOARD_IMI_OV10640_I2C_ADDR_3,                  /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2PX_OV10640_0,              /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2PX_OV10640_IMI_3,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */     \
            NULL,                                          /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2xx,                 /* powerOnDev */    \
        },                                                                              \
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

#endif  /* #ifndef BSP_BOARD_TDA2PX_DEFAULT_H_ */

/* @} */
