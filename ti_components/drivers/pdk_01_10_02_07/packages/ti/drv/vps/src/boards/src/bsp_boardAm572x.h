/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file bsp_boardAm572x.h
 *
 *  \brief AM572x EVM data.
 */

#ifndef BSP_BOARD_AM572X_EVM_DEFAULT_H_
#define BSP_BOARD_AM572X_EVM_DEFAULT_H_

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

#define VPS_CAPT_DRV_ID_AM57XX_IDK_DEFAULT_OV2659       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_AM572X_GP_DEFAULT_OV1063X       (FVID2_VPS_CAPT_VID_DRV)

#if defined (SOC_AM571x)
#define VPS_CAPT_DRV_INST_ID_AM57XX_IDK_DEFAULT_OV2659 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB))
#endif

#if defined (SOC_AM572x) || defined (SOC_AM574x)
#define VPS_CAPT_DRV_INST_ID_AM57XX_IDK_DEFAULT_OV2659 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB))
#define VPS_CAPT_DRV_INST_ID_AM572X_GP_DEFAULT_OV1063X \
      (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA))
#endif

#else

#define VPS_CAPT_DRV_ID_AM57XX_IDK_DEFAULT_OV2659       (0U)
#define VPS_CAPT_DRV_INST_ID_AM57XX_IDK_DEFAULT_OV2659  (0U)

#endif

#ifdef VPS_DSS_BUILD

#define VPS_DSS_DRV_ID_AM57XX_DEFAULT_LCD           (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_AM57XX_DEFAULT_LCD      (VPS_DSS_DISPC_OVLY_DPI1)

#else

#define VPS_DSS_DRV_ID_AM57XX_DEFAULT_LCD           (0U)
#define VPS_DSS_DRV_INST_ID_AM57XX_DEFAULT_LCD      (0U)

#endif

#define BSP_DEVICE_I2C_INST_ID_AM57XX_IDK_OV2659    (BSP_DEVICE_I2C_INST_ID_0)
#define BSP_DEVICE_I2C_INST_ID_AM572X_GP_OV1063X    (BSP_DEVICE_I2C_INST_ID_4)


#define BSP_BOARD_GP_AM572X_DEFAULT_DEVDATA                                     \
    {                                                                           \
        {                                                                       \
            FVID2_LCD_CTRL_DRV,                        /* devDrvId */           \
            0U,                                        /* instId */             \
            BSP_DEVICE_I2C_INST_ID_4,                  /* i2cInstId */          \
            BOARD_AM572x_GP_LCD_MODULE_I2C_ADDR0,      /* i2cAddr */            \
            VPS_DSS_DRV_ID_AM57XX_DEFAULT_LCD,         /* drvId */              \
            VPS_DSS_DRV_INST_ID_AM57XX_DEFAULT_LCD,    /* drvInstId */          \
            NULL,                                      /* selectDev */          \
            NULL,                                      /* resetDev  */          \
            &Bsp_boardPowerOnDeviceAm572xGp,           /* powerOnDev */         \
        },                                                                      \
        {                                                                       \
            FVID2_VID_SENSOR_OV1063X_DRV,                 /* devDrvId */        \
            BSP_DEVICE_OV1063X_INST_ID_4,                 /* instId */          \
            BSP_DEVICE_I2C_INST_ID_AM572X_GP_OV1063X,     /* i2cInstId */       \
            BOARD_OV1063x_I2C_ADDR_0,                     /* i2cAddr */         \
            VPS_CAPT_DRV_ID_AM572X_GP_DEFAULT_OV1063X,    /* drvId */           \
            VPS_CAPT_DRV_INST_ID_AM572X_GP_DEFAULT_OV1063X,   /* drvInstId */   \
            NULL,                                         /* selectDev */       \
            NULL,                                         /* resetDev */        \
            &Bsp_boardPowerOnDeviceAm572xGp,              /* powerOnDev */      \
        }                                                                       \
    }

#define BSP_BOARD_IDK_AM57XX_DEFAULT_DEVDATA                                    \
    {                                                                           \
        {                                                                       \
            FVID2_LCD_CTRL_DRV,                        /* devDrvId */           \
            0U,                                        /* instId */             \
            BSP_DEVICE_I2C_INST_ID_0,                  /* i2cInstId */          \
            BOARD_TC358778_MIPI_DSI_I2C_ADDR0,         /* i2cAddr */            \
            VPS_DSS_DRV_ID_AM57XX_DEFAULT_LCD,         /* drvId */              \
            VPS_DSS_DRV_INST_ID_AM57XX_DEFAULT_LCD,  /* drvInstId */            \
            NULL,                                      /* selectDev */          \
            NULL,                                      /* resetDev */           \
           &Bsp_boardPowerOnDeviceAm572xIdk,           /* powerOnDev  */        \
        },                                                                      \
        {                                                                       \
            FVID2_VID_SENSOR_OV2659_DRV,                 /* devDrvId */         \
            BSP_DEVICE_AM57XIDK_OV2659_INST_ID_0,        /* instId */           \
            BSP_DEVICE_I2C_INST_ID_AM57XX_IDK_OV2659,     /* i2cInstId */       \
            BOARD_OV2659_I2C_ADDR_0,                     /* i2cAddr */          \
            VPS_CAPT_DRV_ID_AM57XX_IDK_DEFAULT_OV2659,   /* drvId */            \
            VPS_CAPT_DRV_INST_ID_AM57XX_IDK_DEFAULT_OV2659,   /* drvInstId */   \
            NULL,                                         /* selectDev */       \
            NULL,                                         /* resetDev */        \
            &Bsp_boardPowerOnDeviceAm572xIdk,             /* powerOnDev */      \
        }                                                                       \
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

#endif  /* #ifndef BSP_BOARD_AM572X_EVM_DEFAULT_H_ */

/* @} */
