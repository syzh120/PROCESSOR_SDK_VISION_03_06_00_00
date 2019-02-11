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
 *  \file bsp_devicePriv.h
 *
 *  \brief BSP device private header file.
 *
 */

#ifndef BSP_DEVICE_PRIV_H_
#define BSP_DEVICE_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if defined (VPS_TI_RTOS_I2C)
#include <ti/csl/tistdtypes.h>
#include <ti/drv/i2c/I2C.h>
#else
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sysbios/knl/Semaphore.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#if !defined (VPS_TI_RTOS_I2C)
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if !defined (VPS_TI_RTOS_I2C)
/*
 *  GIO_Params_init will initialize the async packet to 2.
 */
#define I2C_ASYNC_IOM_PACKET_MAX                                            (2U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32            i2cDebugEnable;
#if defined (VPS_TI_RTOS_I2C)
    I2C_Handle        i2cHndl[BSP_DEVICE_I2C_INST_ID_MAX];
#else
    GIO_Handle        i2cHndl[BSP_DEVICE_I2C_INST_ID_MAX];
    GIO_Struct        i2cGioStruct[BSP_DEVICE_I2C_INST_ID_MAX];
    SyncSem_Struct    i2cSyncSemStruct[BSP_DEVICE_I2C_INST_ID_MAX];
    Semaphore_Struct  i2cSemStruct[BSP_DEVICE_I2C_INST_ID_MAX];
    IOM_Packet        i2cIomPacket[BSP_DEVICE_I2C_INST_ID_MAX]
    [I2C_ASYNC_IOM_PACKET_MAX];
#endif
    BspOsal_SemHandle i2cHndlLock[BSP_DEVICE_I2C_INST_ID_MAX];
} Bsp_DeviceObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_deviceI2cInit(void);
Int32 Bsp_deviceI2cDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_DEVICE_PRIV_H_ */
