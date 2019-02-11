/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file bsp_i2cdrv.h
 *
 *  \brief I2C driver interface file.
 *
 */
#ifndef BSP_I2CDRV_H_
#define BSP_I2CDRV_H_

#include <xdc/std.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/sysbios/io/IOM.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*! To disable/enable entry level parameter checking in the module APIs       */
#define I2c_paramCheckEnable        (TRUE)

#if defined (__TI_ARM_V7M4__) || defined (BUILD_M3)
#define I2C_IRQ_TIME_OUT    5000
#elif defined (_TMS320C6X)
#define I2C_IRQ_TIME_OUT    7000
#elif defined (__ARM_ARCH_7A__) || defined (BUILD_A8)
#define I2C_IRQ_TIME_OUT    10000
#else
/* default timeout if BUILD_xxx is not set */
#define I2C_IRQ_TIME_OUT    5000
#endif

/**
 *  \brief I2c IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern const IOM_Fxns I2c_IOMFXNS;

#ifdef __cplusplus
}
#endif /* extern "C"                                                          */

#endif /* BSP_I2CDRV_H_                                 */
