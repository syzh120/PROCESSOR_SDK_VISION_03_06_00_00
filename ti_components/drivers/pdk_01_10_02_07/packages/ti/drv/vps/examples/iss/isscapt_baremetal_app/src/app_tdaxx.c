/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/i2c/inc/i2c.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>

#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/devices/stw_device.h>

#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CAL_APP_UTIL                "CAL App "
#define CAL_APP_ERR                 " : Error :"
#define CAL_APP_INFO                " Info : "

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
} CalAppUtils_Ub95xI2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static CalAppUtils_Ub95xI2cParams gUb954Cfg[]={
    {0x4c, 0x01, 0x100},
    {0x58, 0X5e, 0x100},
    {0x1f, 0x02, 0x100},
    {0x12, 0x13, 0x100},
    {0x32, 0x01, 0x100},
    {0x33, 0x03, 0x100},
    {0xB0, 0x00, 0x100}, /* Indirect access to pattern generator */
    {0xB1, 0x01, 0x100}, /* Select Reg PGEN_CTL */
    {0xB2, 0x01, 0x100}, /* Write 1 to it */
    {0x20, 0x00, 0x100}
    };

/* NOTE : Expect to see color bar, where the color values should be default
    i.e. first bar = 0xAA, 2nd Bar = 0x33, 3rd bar = 0xF0, 4th bar = 0x7F
        5th bar = 0x55, 6th bar = 0xCC, 7th bar = 0x0F and 8th bar = 0x80 */

static void udelay(int delay_usec)
{
    volatile int a;
    uint32_t delay_msec;
    uint32_t i;

    delay_msec = (delay_usec / 1000);
    if(delay_msec == 0)
    {
        delay_msec = 1;
    }
    for (i = 0; i < (delay_msec * 100); i++)
    {
        a = 0;
    }

    return;
}

/* ========================================================================== */
/*                          Function Implementation                           */
/* ========================================================================== */
void CalAppUtils_BoardInit(void)
{
    stwAppInitParams_t stwAppIniParam;

    /* Workaround: Wait for SBL running on host proc to complete. Otherwise
     * SBL and this app will write to UART, corrupting the console output */
    StwUtils_appWaitForSbl();

    StwUtils_appInitParams_init(&stwAppIniParam);

    StwUtils_appDefaultInit(stwAppIniParam);
}

void CalAppUtils_appInitUb954_Ub953(void)
{
    uint32_t idx, numRegs;
    uint8_t ub954I2CAddr = UB954_I2C_ADDRESS;
    LLD_hsi2cErrorCode_t i2cRtnVal;

    {
        DEVICEI2cProbeAll(HSI2C_INST_1);

        numRegs = sizeof(gUb954Cfg) / (sizeof(gUb954Cfg[0]));
        for (idx = 0U; idx < numRegs; idx++)
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_INFO "Configuring %d of %d\r\n", idx, numRegs);
            i2cRtnVal = DEVICEI2cWrite8(HSI2C_INST_1,
                                                (uint32_t) ub954I2CAddr,
                                                &(gUb954Cfg[idx].nRegAddr),
                                                &(gUb954Cfg[idx].nRegValue),
                                                (UInt32) 1U);
            if (STW_SOK != i2cRtnVal)
            {
                UARTprintf(CAL_APP_UTIL CAL_APP_ERR "Could not configure UB954 !!!\r\n");
                UARTprintf(CAL_APP_UTIL CAL_APP_ERR "Configured %d/%d regs !!!\r\n",
                        idx, numRegs);
                break;
            }

            if (0 != gUb954Cfg[idx].nDelay)
            {
                udelay(gUb954Cfg[idx].nDelay);
            }
        }

        DEVICEI2cProbeAll(HSI2C_INST_1);

        if (STW_SOK == i2cRtnVal)
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                                "Sensor, Configured UB954 !!!\r\n");
        }
    }

    return;
}

void CalAppUtils_appDeInitUb954_Ub953(void)
{
    uint8_t regAddr, regValue;
    LLD_hsi2cErrorCode_t i2cRtnVal;
    uint8_t ub954I2CAddr = UB954_I2C_ADDRESS;

    /* Disable Forwarding */
    regAddr = 0x20;
    regValue = 0x48;

    i2cRtnVal = DEVICEI2cWrite8(HSI2C_INST_1,
                                (uint32_t) ub954I2CAddr,
                                &(regAddr),
                                &(regValue),
                                (UInt32) 1U);
    if (STW_SOK != i2cRtnVal)
    {
        UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                        "Could not disable forwarding UB954 !!!\r\n");
    }
    else
    {
        UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                        "Sensor, Disabled Forwarding !!!\r\n");
        /* Reset */
        regAddr = 0x01;
        regValue = 0x03;

        i2cRtnVal = DEVICEI2cWrite8(HSI2C_INST_1,
                                    (uint32_t) ub954I2CAddr,
                                    &(regAddr),
                                    &(regValue),
                                    (UInt32) 1U);
        if (STW_SOK != i2cRtnVal)
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR "Could not reset UB954 !!!\r\n");
        }
        else
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                        "Sensor, Reset UB954 !!!\r\n");
        }
    }
}

void CalAppUtils_IntrInit(void)
{
    Intc_Init();

    /* XBAR ISS_IRQ_INT0 to IPU1_33 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_33, ISS_IRQ_INT0);
}
