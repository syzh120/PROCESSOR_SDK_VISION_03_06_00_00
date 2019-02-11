/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file stw_device_ioexp_tca64xx.c
 *
 *  \brief TCA64xx (16/24) I2C IO expander driver file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/devices/stw_deviceIoexp.h>
#include <stw_deviceI2cPriv.h>
#include <stw_deviceIoexpPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DEVICE_IOEXP_TCA6424_CMD_AUTO_INC            (0x80U)

/* Input status register */
#define DEVICE_IOEXP_TCA6424_REG_INPUT0              (0x00U)
#define DEVICE_IOEXP_TCA6424_REG_INPUT1              (0x01U)
#define DEVICE_IOEXP_TCA6424_REG_INPUT2              (0x02U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT0             (0x04U)
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT1             (0x05U)
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT2             (0x06U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define DEVICE_IOEXP_TCA6424_REG_POLARITY0           (0x08U)
#define DEVICE_IOEXP_TCA6424_REG_POLARITY1           (0x09U)
#define DEVICE_IOEXP_TCA6424_REG_POLARITY2           (0x0AU)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define DEVICE_IOEXP_TCA6424_REG_CONFIG0             (0x0CU)
#define DEVICE_IOEXP_TCA6424_REG_CONFIG1             (0x0DU)
#define DEVICE_IOEXP_TCA6424_REG_CONFIG2             (0x0EU)

/* Input status register */
#define DEVICE_IOEXP_TCA6416_REG_INPUT0              (0x00U)
#define DEVICE_IOEXP_TCA6416_REG_INPUT1              (0x01U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define DEVICE_IOEXP_TCA6416_REG_OUTPUT0             (0x02U)
#define DEVICE_IOEXP_TCA6416_REG_OUTPUT1             (0x03U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define DEVICE_IOEXP_TCA6416_REG_POLARITY0           (0x04U)
#define DEVICE_IOEXP_TCA6416_REG_POLARITY1           (0x05U)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define DEVICE_IOEXP_TCA6416_REG_CONFIG0             (0x06U)
#define DEVICE_IOEXP_TCA6416_REG_CONFIG1             (0x07U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief IO expander global driver object.
 */
typedef struct deviceIoexpObj
{
    int32_t initValue;
} deviceIoexpObj_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all IO expanders
 */
static deviceIoexpObj_t gDeviceIoexpObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for IO expander driver
 *
 *  This API
 *      - gets called as part of Stw_deviceInit()
 *
 *  \return                 Returns STW_SOK on success else returns
 *                          failure.
 */
int32_t DEVICEIoexpInit(void)
{
    int32_t retVal = STW_SOK;
    int32_t initValue;

    /* Memset global object */
    memset(&gDeviceIoexpObj, 0, sizeof (gDeviceIoexpObj));

    initValue = (int32_t) 1;
    gDeviceIoexpObj.initValue = initValue;

    return (retVal);
}

/**
 *  \brief System de-init for IO expander driver
 *
 *  This API
 *      - gets called as part of Stw_deviceDeInit()
 *
 *  \return                 Returns STW_SOK on success else returns
 *                          failure.
 */
int32_t DEVICEIoexpDeInit(void)
{
    return (STW_SOK);
}

int32_t DEVICEIoexpTca6424WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_CONFIG0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }
    return (retVal);
}

int32_t DEVICEIoexpTca6424WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_OUTPUT0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = ((uint8_t) DEVICE_IOEXP_TCA6424_REG_OUTPUT0 |
                              (uint8_t) DEVICE_IOEXP_TCA6424_CMD_AUTO_INC) +
                              (uint8_t) cnt;
            retVal = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = ((uint8_t) DEVICE_IOEXP_TCA6424_REG_INPUT0 |
                              (uint8_t) DEVICE_IOEXP_TCA6424_CMD_AUTO_INC) +
                              (uint8_t) cnt;
            retVal = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_POLARITY0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_CONFIG0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_OUTPUT0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = (uint8_t) DEVICE_IOEXP_TCA6416_REG_OUTPUT0 +
                             (uint8_t) cnt;
            retVal         = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = (uint8_t) DEVICE_IOEXP_TCA6416_REG_INPUT0 +
                             (uint8_t) cnt;
            retVal         = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_POLARITY0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

