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
 *  \file bspdrv_lcdCtrlPriv.h
 *
 *  \brief LCD Controller internal header file.
 */

#ifndef BSP_LCDCTRL_PRIV_H_
#define BSP_LCDCTRL_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_lcdController.h>
#include <lcdCtrl/bspdrv_lcdCtrl.h>
#include <tlc59108/bsp_tlc59108.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_LCDCTRL_THREEFIVE_ENBKL       ((UInt32) BSP_TLC59108_PIN0)

#define BSP_LCDCTRL_THREEFIVE_AVDD_EN     ((UInt32) BSP_TLC59108_PIN1)

#define BSP_LCDCTRL_THREEFIVE_PWM         ((UInt32) BSP_TLC59108_PIN2)

#define BSP_LCDCTRL_THREEFIVE_STBYB       ((UInt32) BSP_TLC59108_PIN3)

#define BSP_LCDCTRL_THREEFIVE_UPDN        ((UInt32) BSP_TLC59108_PIN4)

#define BSP_LCDCTRL_THREEFIVE_DITH        ((UInt32) BSP_TLC59108_PIN5)

#define BSP_LCDCTRL_THREEFIVE_MODE3       ((UInt32) BSP_TLC59108_PIN6)

#define BSP_LCDCTRL_THREEFIVE_SHLR        ((UInt32) BSP_TLC59108_PIN7)

#define BSP_LCDCTRL_TLC59108_INST_0       (0x0)

#define BSP_LCDCTRL_TLC59108_INST_1       (0x1)

/** \brief Driver object state - NOT IN USE. */
#define BSP_LCDCTRL_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_LCDCTRL_OBJ_STATE_IDLE      (1U)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/* Use 32 FPS configuration for TDA2xx and TDA2ex for IDK LCD */
#define BSP_LCDCTRL_IDK_LCD_32FPS       (1U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TVP5158 driver handle object.
 */
typedef struct
{
    UInt32                  state;
    /**< Handle state - used or free. */
    UInt32                  handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle       lock;
    /**< Driver lock. */
    Bsp_LcdCtrlCreateParams createPrms;
    /**< Create time arguments. */
} Bsp_LcdCtrlHandleObj;

/**
 *  \brief TVP5158 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_LcdCtrlHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_LcdCtrlObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void Tc358778_lcdBridgeInit(UInt32 deviceI2cInstId, UInt32 slaveAddr, UInt32 peripheralCmdOn);
void Tc358778_lcdBridgeDeinit(UInt32 deviceI2cInstId, UInt32 slaveAddr);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_LCDCTRL_PRIV_H_ */
