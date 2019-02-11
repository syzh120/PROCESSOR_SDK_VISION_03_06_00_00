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
 *  \file bsp_boardTda2exDefault.h
 *
 *  \brief Tda2ex default (base) board data.
 */

#ifndef BSP_BOARD_TDA2EX_DEFAULT_H_
#define BSP_BOARD_TDA2EX_DEFAULT_H_

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

/* Below are the sensors connected to VIN1A */
#define VPS_CAPT_DRV_ID_TDA2EX_LI_OV1063X_0     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA2EX_LI_OV1063X_0 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2EX_LI_OV1063X_0         (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_LI_OV1063X_0    (0U)

#endif

#ifdef VPS_DSS_BUILD

#define VPS_DSS_DRV_ID_TDA2EX_DEFAULT_LCD           (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA2EX_DEFAULT_LCD      (VPS_DSS_DISPC_OVLY_DPI1)

#define VPS_DSS_DRV_INST_ID_TDA2EX_17X17_DEFAULT_LCD    (VPS_DSS_DISPC_OVLY_DPI3)

#else

#define VPS_DSS_DRV_ID_TDA2EX_DEFAULT_LCD           (0U)
#define VPS_DSS_DRV_INST_ID_TDA2EX_DEFAULT_LCD      (0U)

#define VPS_DSS_DRV_INST_ID_TDA2EX_17X17_DEFAULT_LCD    (0U)
#endif

#ifdef VPS_CAL_BUILD

#define VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_0    (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_1    (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_2    (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_3    (VPS_CAPT_INST_ISS_CAL_A + 3U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_0   (VPS_CAPT_INST_ISS_CAL_A)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_1   (VPS_CAPT_INST_ISS_CAL_A + 1U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_2   (VPS_CAPT_INST_ISS_CAL_A + 2U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_3   (VPS_CAPT_INST_ISS_CAL_A + 3U)

#else

#define VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID               (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_0            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_1            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_2            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_3            (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_0           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_1           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_2           (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_OV10635_3           (0U)

#endif

#define BSP_BOARD_TDA2EX_DEFAULT_DEVDATA                                    \
    {                                                                       \
        {                                                                   \
            FVID2_LCD_CTRL_DRV,                         /* devDrvId */      \
            0U,                                         /* instId */        \
            BSP_DEVICE_I2C_INST_ID_0,                   /* i2cInstId */     \
            BOARD_TLC59108_I2C_ADDR_0,                  /* i2cAddr */       \
            VPS_DSS_DRV_ID_TDA2EX_DEFAULT_LCD,          /* drvId */         \
            VPS_DSS_DRV_INST_ID_TDA2EX_DEFAULT_LCD,     /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_LCD_CTRL_DRV,                          /* devDrvId */      \
            1U,                                          /* instId */        \
            BSP_DEVICE_I2C_INST_ID_0,                    /* i2cInstId */     \
            BOARD_TLC59108_I2C_ADDR_0,                   /* i2cAddr */       \
            VPS_DSS_DRV_ID_TDA2EX_DEFAULT_LCD,           /* drvId */         \
            VPS_DSS_DRV_INST_ID_TDA2EX_17X17_DEFAULT_LCD,/* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,                /* selectDev */     \
            NULL,                                        /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,               /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,            /* devDrvId */      \
            BSP_DEVICE_LI_OV1063X_INST_ID_0,            /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                   /* i2cInstId */     \
            BOARD_LI_OV1063X_I2C_ADDR_0,                /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_LI_OV1063X_0,        /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2EX_LI_OV1063X_0,   /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        /* ENET PHY on base board goes to ENET PORT 0 */                    \
        {                                                                   \
            BSP_DRV_ID_ENET_PHY_DP83865,                /* devDrvId */      \
            BSP_DEVICE_ENET_PHY_DP83865_INST_ID_0,      /* instId */        \
            BSP_DEVICE_I2C_INST_ID_MAX,                 /* i2cInstId */     \
            0U,                                         /* i2cAddr */       \
            BSP_DRV_ID_ENET,                            /* drvId */         \
            BSP_DEVICE_ENET_PORT_INST_ID_0,             /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            NULL,                                       /* powerOnDev */    \
        },                                                                  \
        /* Same ENET PHY on base board goes to ENET PORT 1 */               \
        {                                                                   \
            BSP_DRV_ID_ENET_PHY_DP83865,                /* devDrvId */      \
            BSP_DEVICE_ENET_PHY_DP83865_INST_ID_1,      /* instId */        \
            BSP_DEVICE_I2C_INST_ID_MAX,                 /* i2cInstId */     \
            0U,                                         /* i2cAddr */       \
            BSP_DRV_ID_ENET,                            /* drvId */         \
            BSP_DEVICE_ENET_PORT_INST_ID_1,             /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            NULL,                                       /* powerOnDev */    \
        },                                                                  \
        {                                                                    \
            BSP_DRV_ID_MMC,                                /* devDrvId */    \
            BSP_DEVICE_MMC_INST_ID_1,                      /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2ex,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            &Bsp_boardPowerOnDeviceTda2ex,                 /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,  /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,        /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                   /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_0,      /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID,          /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_0,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,  /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,        /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                   /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_1,      /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID,          /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_1,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,  /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,        /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                   /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_2,      /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID,          /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_2,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,  /* devDrvId */      \
            BSP_DEVICE_APT_AR0140_INST_ID_0_ISS,        /* instId */        \
            BSP_DEVICE_I2C_INST_ID_4,                   /* i2cInstId */     \
            BOARD_APT_TIDA00262_AR0140_I2C_ADDR_3,      /* i2cAddr */       \
            VPS_CAPT_DRV_ID_TDA2EX_CAL_DRV_ID,          /* drvId */         \
            VPS_CAPT_DRV_INST_ID_TDA2EX_AR0140_3,       /* drvInstId */     \
            &Bsp_boardSelectDeviceTda2ex,               /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
        },                                                                  \
        {                                                                   \
            FVID2_VID_ETHSRV_CAM_DRV,  /* devDrvId */                       \
            BSP_DEVICE_ETH_CAM_INST_ID_0,        /* instId */               \
            NULL,                   /* i2cInstId */                         \
            NULL,      /* i2cAddr */                                        \
            NULL,          /* drvId */                                      \
            NULL,       /* drvInstId */                                     \
            NULL,                                       /* selectDev */     \
            NULL,                                       /* resetDev */      \
            &Bsp_boardPowerOnDeviceTda2ex,              /* powerOnDev */    \
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

#endif  /* #ifndef BSP_BOARD_TDA2EX_DEFAULT_H_ */

/* @} */
