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
 *  \file stw_boardTda2xxVision.h
 *
 *  \brief Tda2xx Vision board data.
 */

#ifndef STW_BOARD_TDA2XX_VISION_H_
#define STW_BOARD_TDA2XX_VISION_H_

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
#if defined (SOC_TDA2PX)
#define OV1063X_DEVICE_I2C_INST_ID                 (DEVICE_I2C_INST_ID_4)
#else
#define OV1063X_DEVICE_I2C_INST_ID                 (DEVICE_I2C_INST_ID_1)
#endif

#define BOARD_TDA2XX_VISION_DEVDATA                                     \
    {                                                                   \
        {                                          /* EEPROM */         \
            DEVICE_ID_EEPROM,                      /* devId */          \
            0U,                                    /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            0U,                                    /* ctrlModInstNum */ \
            BOARD_EEPROM_I2C_ADDR_0,               /* ctrlInfo */       \
            BOARD_INVALID_ID,                      /* dataModId */      \
            BOARD_INVALID_INST_NUM,                /* dataModInstNum */ \
            NULL,                                  /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* UART */           \
            DEVICE_ID_UART,                        /* devId */          \
            0U,                                    /* devInstNum */     \
            BOARD_INVALID_ID,                      /* ctrlModId */      \
            BOARD_INVALID_INST_NUM,                /* ctrlModInstNum */ \
            BOARD_INVALID_INFO,                    /* ctrlInfo */       \
            DEVICE_ID_UART,                        /* dataModId */      \
            0U,                                    /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xxVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* Temp Sensor */    \
            DEVICE_ID_TMP102,                      /* devId */          \
            0U,                                    /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            0U,                                    /* ctrlModInstNum */ \
            BOARD_TEMP_SENSOR_I2C_ADDR,            /* ctrlInfo */       \
            BOARD_INVALID_ID,                      /* dataModId */      \
            BOARD_INVALID_INST_NUM,                /* dataModInstNum */ \
            NULL,                                  /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* OV Sensor */      \
            DEVICE_ID_OV1063X,                     /* devId */          \
            DEVICE_OV1063X_INST_ID_0,              /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            OV1063X_DEVICE_I2C_INST_ID,            /* ctrlModInstNum */ \
            BOARD_OV1063x_I2C_ADDR_0,              /* ctrlInfo */       \
            DEVICE_MODULE_ID_VIP,                  /* dataModId */      \
            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xxVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2xx              /* pFnPowerOnDev */  \
        },                                                              \
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

#endif  /* #ifndef STW_BOARD_TDA2XX_VISION_H_ */

/* @} */
