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
 *  \file bsp_boardTda3xxGenericAlps.h
 *
 *  \brief Tda3xx AR12xx Radar Generic Alps Board Data
 */

#ifndef BSP_BOARD_TDA3XX_GENERIC_ALPS_H_
#define BSP_BOARD_TDA3XX_GENERIC_ALPS_H_

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

#define BSP_BOARD_TDA3XX_GENERIC_ALPS_DEVDATA                               \
    {                                                                       \
        {                                                                   \
            BSP_DRV_ID_UART,                               /* devDrvId */   \
            BSP_DEVICE_UART_INST_ID_0,                     /* instId */     \
            NULL,                                          /* i2cInstId */  \
            NULL,                                          /* i2cAddr */    \
            NULL,                                          /* drvId */      \
            NULL,                                          /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */  \
            NULL,                                          /* resetDev */   \
            NULL,                                          /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            BSP_DRV_ID_UART,                               /* devDrvId */   \
            BSP_DEVICE_UART_INST_ID_1,                     /* instId */     \
            NULL,                                          /* i2cInstId */  \
            NULL,                                          /* i2cAddr */    \
            NULL,                                          /* drvId */      \
            NULL,                                          /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */  \
            NULL,                                          /* resetDev */   \
            NULL,                                          /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            BSP_DRV_ID_UART,                               /* devDrvId */   \
            BSP_DEVICE_UART_INST_ID_2,                     /* instId */     \
            NULL,                                          /* i2cInstId */  \
            NULL,                                          /* i2cAddr */    \
            NULL,                                          /* drvId */      \
            NULL,                                          /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */  \
            NULL,                                          /* resetDev */   \
            NULL,                                          /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            BSP_DRV_ID_MCSPI,                              /* devDrvId */   \
            BSP_DEVICE_MCSPI_INST_ID_0,                    /* instId */     \
            NULL,                                          /* i2cInstId */  \
            NULL,                                          /* i2cAddr */    \
            NULL,                                          /* drvId */      \
            NULL,                                          /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                  /* selectDev */  \
            NULL,                                          /* resetDev */   \
            NULL,                                          /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            BSP_DRV_ID_MMC,                                /* devDrvId */   \
            BSP_DEVICE_MMC_INST_ID_4,                      /* instId */     \
            NULL,                                          /* i2cInstId */  \
            NULL,                                          /* i2cAddr */    \
            NULL,                                          /* drvId */      \
            NULL,                                          /* drvInstId */  \
            NULL,                                          /* selectDev */  \
            NULL,                                          /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                 /* powerOnDev */ \
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

#endif  /* #ifndef BSP_BOARD_TDA3XX_GENERIC_ALPS_H_ */

/* @} */
