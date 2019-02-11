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
 *  \file stw_boardTda2exVision.h
 *
 *  \brief Tda2ex Vision board data.
 */

#ifndef STW_BOARD_TDA2EX_VISION_H_
#define STW_BOARD_TDA2EX_VISION_H_

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

#define BOARD_TDA2EX_VISION_DEVDATA                                     \
    {                                                                   \
        {                                          /* OV Sensor */      \
            DEVICE_ID_OV1063X,                     /* devId */          \
            DEVICE_OV1063X_INST_ID_0,              /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            DEVICE_I2C_INST_ID_4,                  /* ctrlModInstNum */ \
            BOARD_OV1063x_I2C_ADDR_0,              /* ctrlInfo */       \
            DEVICE_MODULE_ID_VIP,                  /* dataModId */      \
            DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda2exVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2ex              /* pFnPowerOnDev */  \
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

#endif  /* #ifndef STW_BOARD_TDA2EX_VISION_H_ */

/* @} */
