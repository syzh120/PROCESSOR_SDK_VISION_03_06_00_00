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
 *  \defgroup BSP_DRV_I2C_API BSP I2C Driver API
 *
 *  @{
 */

/**
 *  \file bsp_i2c.h
 *
 *  \brief I2C Driver Interface.
 */

#ifndef BSP_I2C_H_
#define BSP_I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief  I2C Ioctl commands
 *
 *  I2C Ioctl commands
 */
typedef enum {
    IOCTL_I2C_PROBE,
    /** < IOCTL for probing the i2c instance>*/
    IOCTL_I2C_GET_BUS_FREQUENCY,
    /** < IOCTL to get I2C Bus frequency>*/
    IOCTL_I2C_SET_BUS_FREQUENCY,
    /** < IOCTL to set I2C Bus frequency>*/
    IOCTL_I2C_RESET_CONTROLLER,
    /** < IOCTL reset I2C controller>*/
    IOCTL_I2C_RECOVER_BUS
    /** < IOCTL to force 9 clk pulses>*/
}I2c_IOCTL;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief I2C Device Initialization Object
 *
 *  This structure provides Initalization Routines.
 *  It needs to be passed while creating the specific I2C instance object.
 */
typedef struct
{
    lld_hsi2c_initParam_t *initParams;
    /**< lld_hsi2c_initParam_s contains the I2C initialisation parameters.*/
    BspOsal_SemHandle      hsi2c_sem;
    /**< hsi2c_sem semaphore handle that needs to be passed by application*/
    UInt32                 instId;
    /**< instId Instance Id of the instance, needs to be passed by application*/
} I2c_DevInitParams;

/**
 *  \brief Initialize I2C controller(s)
 *
 *  Initializes I2C controller(s) with the initPrms structure. User should pass
 *  configuration information for numInst controllers.
 *  This function should be called before calling any of driver APIs and
 *  should be called only once.
 *
 *  \param  numInst     [IN]    Number of I2C controllers need to be
 *                              initialized
 *  \param  devInitPrms    [IN]    Configuration for numInst controllers.
 *
 *  \return IOM_COMPLETED on success else appropriate error code on failure.
 */

Int32 I2c_GlobalInit(UInt32 numInst, I2c_DevInitParams *devInitPrms);
/**
 *  \brief De-initializes I2C Instances
 *
 *  De-initializes the I2C controllers. If there are open handles,
 *  they are invalidated. It should be called only after calling Bsp_i2cInit
 *  and in the end when I2C driver is no more required by any user.
 *
 *  \param args         [IN] Not used currently. Meant for future purpose.
 *
 *  \return IOM_COMPLETED on success else appropriate error code on failure.
 */
Int32 I2c_GlobalDeInit(Ptr args);
#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_I2C_H_ */

/* @} */
/**
 * \mainpage  I2C Library
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * I2C Library contains the I2C API files and APIs to control IO expanders.
 * I2C could be used to read / write into any of the video on-board devices
 * such as Sii9022a, TVP7002, IO Expanders or sensors such as MT9V022, etc.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *  - <b> BSP I2C Library(BSP_LLD_I2C)
 * </b> (See \ref BSP_DRV_I2C_API) <br>
 *  - <b> HS I2C Library(HS_I2C_LLD_API)
 * </b> (See \ref HS_I2C_LLD_API) <br>
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */
