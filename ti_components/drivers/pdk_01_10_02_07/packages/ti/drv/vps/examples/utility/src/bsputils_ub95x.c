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
 *  \file bsputils_ub95x.c
 *
 *  \brief Implements APIs to initialize, de-initialize UB954 * UB953 EVM,
 *           address aliases & reset sensors.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_ub95x.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< UB954 I2C Address */
#define UB954_I2C_ADDRESS           (0x3D)

/**< UB953 I2C Address */
#define UB953_I2C_ADDRESS           (0x18)
/**< UB953 Alias I2C Address */
#define UB953_I2C_ALIAS_ADDRESS     (0x74)

/**< OV7261 I2C Address */
#define OV7261_I2C_ADDRESS          (0x60)
/**< OV7261 Alias I2C Address */
#define OV7261_I2C_ALIAS_ADDRESS    (0x38)

/**< Temperature sensor I2C Address */
#define TEMP_SENS_I2C_ADDRESS       (0x48)
/**< Temperature sensor Alias I2C Address */
#define TEMP_SENS_I2C_ALIAS_ADDRESS (0x76)

/**< LED Driver I2C Address */
#define LED_DRV_I2C_ADDRESS         (0x49)
/**< LED Driver Alias I2C Address */
#define LED_DRV_I2C_ALIAS_ADDRESS   (0x78)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static BspUtils_Ub95xI2cParams gUb954Cfg[]={
    {0x4c, 0x01, 0x1},
    {0x58, 0X5e, 0x2},
    {0x5b, (UB953_I2C_ADDRESS           << 1U), 0x1},
    {0x5c, (UB953_I2C_ALIAS_ADDRESS     << 1U), 0x1},
    {0x5D, (OV7261_I2C_ADDRESS          << 1U), 0x1},
    {0x65, (OV7261_I2C_ALIAS_ADDRESS    << 1U), 0x1},
    {0x5e, (TEMP_SENS_I2C_ADDRESS       << 1U), 0x1},
    {0x66, (TEMP_SENS_I2C_ALIAS_ADDRESS << 1U), 0x1},
    {0x5f, (LED_DRV_I2C_ADDRESS         << 1U), 0x1},
    {0x67, (LED_DRV_I2C_ALIAS_ADDRESS   << 1U), 0x1},
    {0x1f, 0x02, 0x1},
    {0x12, 0x13, 0x1},
    {0x32, 0x01, 0x1},
    {0x33, 0x03, 0x1},
    {0xB0, 0x00, 0x1}, /* Indirect access to pattern genrator */
    {0xB1, 0x01, 0x1}, /* Select Reg PGEN_CTL */
    {0xB2, 0x01, 0x1}, /* Write 1 to it */
    {0x20, 0x00, 0x1}
    };

/* NOTE : Expect to see color bar, where the color values should be default
    i.e. first bar = 0xAA, 2nd Bar = 0x33, 3rd bar = 0xF0, 4th bar = 0x7F
        5th bar = 0x55, 6th bar = 0xCC, 7th bar = 0x0F and 8th bar = 0x80 */
/* ========================================================================== */
/*                          Function Implementation                           */
/* ========================================================================== */

void BspUtils_appInitUb954_Ub953(BspUtils_Ub95xI2cParams *pCfg,
                                    UInt32 numUb954Regs)
{
    Int32 retVal;
    uint32_t idx, numRegs;
    BspUtils_Ub95xI2cParams *pUb954Cfg = NULL;
    uint8_t ub954I2CAddr = UB954_I2C_ADDRESS;

    if (NULL == pCfg)
    {
        numRegs = sizeof(gUb954Cfg) / (sizeof(gUb954Cfg[0]));
        pUb954Cfg = &gUb954Cfg[0U];
    }
    else
    {
        numRegs = numUb954Regs;
        pUb954Cfg = pCfg;
    }

    for (idx = 0U; idx < numRegs; idx++)
    {
        retVal = Bsp_deviceWrite8(BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST,
                                    ub954I2CAddr,
                                    &((pUb954Cfg + idx)->nRegAddr),
                                    &((pUb954Cfg + idx)->nRegValue),
                                    (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB954 !!!\r\n");
            break;
        }
        if (0 != (pUb954Cfg + idx)->nDelay)
        {
            BspOsal_sleep((pUb954Cfg + idx)->nDelay);
        }
    }
    GT_1trace(BspAppTrace, GT_INFO,
                            "Configured UB954 [%d]!!!\r\n", retVal);
#if NOT_YET
    {
    uint8_t ub953I2CAddr = UB953_I2C_ALIAS_ADDRESS;
    static BspUtils_Ub95xI2cParams gUb953Cfg[]={
        {0x02, 0x02, 0x0},
        {0x0e, 0x40, 0x0},
        {0x0d, 0x04, 0x0},
    };

    numRegs = sizeof(gUb953Cfg) / (sizeof(gUb953Cfg[0]));
    for (idx = 0U; idx < numRegs; idx++)
    {
        retVal = Bsp_deviceWrite8(i2cInst,
                                    ub953I2CAddr,
                                    &(gUb953Cfg[idx].nRegAddr),
                                    &(gUb953Cfg[idx].nRegValue),
                                    (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB953 !!!\r\n");
            break;
        }
        if (0 != gUb953Cfg[idx].nDelay)
        {
            BspOsal_sleep(gUb953Cfg[idx].nDelay);
        }
    }
    }
    GT_1trace(BspAppTrace, GT_INFO,
                        "Configured UB953 [%d]!!!\r\n", retVal);
#endif

    Bsp_deviceI2cProbeAll(BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST);

    return;
}

void BspUtils_appDeInitUb954_Ub953(void)
{
    uint8_t regAddr, regValue;
    Int32 retVal;

    /* Disable Forwarding */
    regAddr = 0x20;
    regValue = 0x48;

    retVal = Bsp_deviceWrite8(BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST,
                                UB954_I2C_ADDRESS,
                                &regAddr,
                                &regValue,
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Could not disable forwarding UB954 !!!\r\n");
    }
    else
    {
        /* Reset */
        regAddr = 0x01;
        regValue = 0x03;

        retVal = Bsp_deviceWrite8(BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST,
                                    UB954_I2C_ADDRESS,
                                    &regAddr,
                                    &regValue,
                                    (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Could not reset UB954 !!!\r\n");
        }
    }

#ifdef NOT_YET
    /* Steps
        1. Power down sensor
        2. Reset UB953
        3. Reset UB954
    */
    Int32 retVal;
    uint32_t i2cInst = BSPUTILS_UB954_ACCESSIBLE_FROM_I2C_INST;
    uint8_t ub954I2CAddr = UB954_I2C_ADDRESS;
    uint8_t ub953I2CAddr = UB953_I2C_ALIAS_ADDRESS;
    uint8_t regAddr, regValue;

    /* Power down sensor */
    regAddr = 0x0e;
    regValue = 0x00;
    retVal = Bsp_deviceWrite8(i2cInst,
                                ub953I2CAddr,
                                &(regAddr),
                                &(regValue),
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Could not power down sensor !!!\r\n");
    }
    /* Reset UB953 */
    regAddr = 0x01;
    regValue = 0x02;
    retVal = Bsp_deviceWrite8(i2cInst,
                                ub953I2CAddr,
                                &(regAddr),
                                &(regValue),
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Could not reset UB953 !!!\r\n");
    }
    /* Reset UB954 */
    regAddr = 0x01;
    regValue = 0x02;
    retVal = Bsp_deviceWrite8(i2cInst,
                                ub954I2CAddr,
                                &(regAddr),
                                &(regValue),
                                (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Could not reset UB954 !!!\r\n");
    }
#endif

}
