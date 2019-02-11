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
 *  \file bspdrv_tlc59108Priv.h
 *
 *  \brief TLC59108 PWM internal header file.
 */

#ifndef BSP_TLC59108_PRIV_H_
#define BSP_TLC59108_PRIV_H_

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
#include <tlc59108/bsp_tlc59108.h>
#include <ti/drv/vps/include/devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_TLC59108_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_TLC59108_OBJ_STATE_IDLE      (1U)

/* Mask for LEDOUT0 and LEDOUT1 registers */
#define BSP_TLC59108_LEDOUT0_PIN0_MASK        (0x03U)   /* 0000 0011*/
#define BSP_TLC59108_LEDOUT0_PIN0_SHIFT       (0x00U)

#define BSP_TLC59108_LEDOUT0_PIN1_MASK        (0x0CU)   /* 0000 1100*/
#define BSP_TLC59108_LEDOUT0_PIN1_SHIFT       (0x02U)

#define BSP_TLC59108_LEDOUT0_PIN2_MASK        (0x30U)   /* 0011 0000*/
#define BSP_TLC59108_LEDOUT0_PIN2_SHIFT       (0x04U)

#define BSP_TLC59108_LEDOUT0_PIN3_MASK        (0xC0U)   /* 1100 0000*/
#define BSP_TLC59108_LEDOUT0_PIN3_SHIFT       (0x06U)

#define BSP_TLC59108_LEDOUT1_PIN4_MASK        (0x03U)   /* 0000 0011*/
#define BSP_TLC59108_LEDOUT1_PIN4_SHIFT       (0x00U)

#define BSP_TLC59108_LEDOUT1_PIN5_MASK        (0x0CU)   /* 0000 1100*/
#define BSP_TLC59108_LEDOUT1_PIN5_SHIFT       (0x02U)

#define BSP_TLC59108_LEDOUT1_PIN6_MASK        (0x30U)   /* 0011 0000*/
#define BSP_TLC59108_LEDOUT1_PIN6_SHIFT       (0x04U)

#define BSP_TLC59108_LEDOUT1_PIN7_MASK        (0xC0U)   /* 1100 0000*/
#define BSP_TLC59108_LEDOUT1_PIN7_SHIFT       (0x06U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TLC59108 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle lock;
    /* Global driver lock. */
} Bsp_Tlc59108Obj;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_TLC59108_PRIV_H_ */
