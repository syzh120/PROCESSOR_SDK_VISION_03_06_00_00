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
 *  \file bsp_boardTda2exJamr3.h
 *
 *  \brief TDA2EX JAMR3 board data.
 */

#ifndef BSP_BOARD_TDA2EX_JAMR3_H_
#define BSP_BOARD_TDA2EX_JAMR3_H_

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

#define VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158        (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158   (0U)

#endif

#define BSP_DEVICE_I2C_INST_ID_JAMR3_TVP5158        (BSP_DEVICE_I2C_INST_ID_4)

#define BSP_BOARD_TDA2EX_JAMR3_DEVDATA                                  \
    {                                                                   \
        {                                                               \
            FVID2_VID_DEC_TVP5158_DRV,                 /* devDrvId */   \
            0U,                                        /* instId */     \
            BSP_DEVICE_I2C_INST_ID_JAMR3_TVP5158,      /* i2cInstId */  \
            BOARD_TVP5158_I2C_ADDR_0,                  /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exJamr3,         /* selectDev */  \
            NULL,                                      /* resetDev */   \
            NULL,                                      /* powerOnDev */ \
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

#endif  /* #ifndef BSP_BOARD_TDA2EX_JAMR3_H_ */

/* @} */
