/* =============================================================================
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
 *  \addtogroup BSPUTILS_UB960_API
 *  @{
 */

/**
 *  \file bsputils_ub960.h
 *
 *  \brief Defines APIs to initialize, de-initialize UB960 EVM, address aliases
 *          & reset sensors.
 *
 *  TODO: Get serializer address function should be common for all modules.
 *          Right now, its seperate for TIDA, SAT0088 & IMI modules
 */

#ifndef BSPUTILS_UB95X_H_
#define BSPUTILS_UB95X_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< I2C Instance to be used */
#if defined (SOC_TDA3XX)
    #ifdef BOARD_TYPE_TDA3XX_RVP
        #define BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST \
                                                    (BSP_DEVICE_I2C_INST_ID_0)
        /**< Identify the I2C instance through which UB954 is accessible */

    #else
        #define BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST \
                                                    (BSP_DEVICE_I2C_INST_ID_1)
        /**< Identify the I2C instance through which UB954 is accessible */

    #endif
#elif defined (SOC_TDA2EX) || defined (SOC_AM571x)

    #define BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_4)
    /**< Identify the I2C instance through which UB954 is accessible */

#elif defined (SOC_TDA2PX)

    #define BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_4)
    /**< Identify the I2C instance through which UB954 is accessible */

#else

    #define BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST  (BSP_DEVICE_I2C_INST_ID_0)
    /**< Identify the I2C instance through which UB954 is accessible */

#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief Register address and value pair, with delay.
 */
typedef struct
{
    UInt8 nRegAddr;
    /**< Register Address */
    UInt8 nRegValue;
    /**< Slave Address */
    UInt32 nDelay;
    /**< Delay to be applied, after the register is programmed */
} BspUtils_Ub95xI2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes the UB954 & UB953.
 *          Initializes UB954, UB953 and configures to access 2 other remote
 *          I2C slaves
 */
void BspUtils_appInitUb954_Ub953(BspUtils_Ub95xI2cParams *pCfg,
                                    UInt32 numUb954Regs);

/**
 *  \brief De Initializes the UB954 & UB953
 *              Turns off power to 1 slave, resets UB953 & UB954
 */
void BspUtils_appDeInitUb954_Ub953(void);


#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_UB95X_H_ */

/* @} */
