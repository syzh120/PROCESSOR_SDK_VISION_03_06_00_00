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
 *  \file stw_boardTda2xxDefault.h
 *
 *  \brief Tda2xx Default board data.
 */

#ifndef STW_BOARD_TDA2XX_DEFAULT_H_
#define STW_BOARD_TDA2XX_DEFAULT_H_

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

#define BOARD_TDA2XX_DEFAULT_DEVDATA                                          \
    {                                                                         \
        {                                                /* EEPROM */         \
            DEVICE_ID_EEPROM,                            /* devId */          \
            0U,                                          /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            0U,                                          /* ctrlModInstNum */ \
            BOARD_EEPROM_I2C_ADDR_0,                     /* ctrlInfo */       \
            BOARD_INVALID_ID,                            /* dataModId */      \
            BOARD_INVALID_INST_NUM,                      /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 1 */         \
            DEVICE_ID_UART,                              /* devId */          \
            1U,                                          /* devInstNum */     \
            BOARD_INVALID_ID,                            /* ctrlModId */      \
            BOARD_INVALID_INST_NUM,                      /* ctrlModInstNum */ \
            BOARD_INVALID_INFO,                          /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            1U,                                          /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 2 */         \
            DEVICE_ID_UART,                              /* devId */          \
            2U,                                          /* devInstNum */     \
            BOARD_INVALID_ID,                            /* ctrlModId */      \
            BOARD_INVALID_INST_NUM,                      /* ctrlModInstNum */ \
            BOARD_INVALID_INFO,                          /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            2U,                                          /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 3 */         \
            DEVICE_ID_UART,                              /* devId */          \
            3U,                                          /* devInstNum */     \
            BOARD_INVALID_ID,                            /* ctrlModId */      \
            BOARD_INVALID_INST_NUM,                      /* ctrlModInstNum */ \
            BOARD_INVALID_INFO,                          /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            3U,                                          /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* Temp Sensor */    \
            DEVICE_ID_TMP102,                            /* devId */          \
            0U,                                          /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            0U,                                          /* ctrlModInstNum */ \
            BOARD_TEMP_SENSOR_I2C_ADDR,                  /* ctrlInfo */       \
            BOARD_INVALID_ID,                            /* dataModId */      \
            BOARD_INVALID_INST_NUM,                      /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* LCD */            \
            DEVICE_ID_LCD,                               /* devId */          \
            DEVICE_LCD_INST_ID_0,                        /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            DEVICE_I2C_INST_ID_0,                        /* ctrlModInstNum */ \
            BOARD_TLC59108_I2C_ADDR_0,                   /* ctrlInfo */       \
            DEVICE_MODULE_ID_DCTRL,                      /* dataModId */      \
            DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2xx                    /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* MMC */            \
            DEVICE_ID_MMC,                               /* devId */          \
            DEVICE_MMC_INST_ID_2,                        /* devInstNum */     \
            BOARD_INVALID_ID,                            /* ctrlModId */      \
            BOARD_INVALID_INST_NUM,                      /* ctrlModInstNum */ \
            BOARD_INVALID_INFO,                          /* ctrlInfo */       \
            BOARD_INVALID_ID,                            /* dataModId */      \
            BOARD_INVALID_INST_NUM,                      /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
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

#endif  /* #ifndef STW_BOARD_TDA2XX_DEFAULT_H_ */

/* @} */
