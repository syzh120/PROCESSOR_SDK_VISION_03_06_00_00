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
 *  \file bspdrv_ioexpTca64xx.c
 *
 *  \brief TCA64xx (16/24) I2C IO expander driver file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_ioexp.h>
#include <ioexp/bspdrv_ioexp.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TCA6424_CMD_AUTO_INC            ((UInt8) 0x80U)

/* Input status register */
#define TCA6424_REG_INPUT0              ((UInt8) 0x00U)
#define TCA6424_REG_INPUT1              ((UInt8) 0x01U)
#define TCA6424_REG_INPUT2              ((UInt8) 0x02U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define TCA6424_REG_OUTPUT0             ((UInt8) 0x04U)
#define TCA6424_REG_OUTPUT1             ((UInt8) 0x05U)
#define TCA6424_REG_OUTPUT2             ((UInt8) 0x06U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define TCA6424_REG_POLARITY0           ((UInt8) 0x08U)
#define TCA6424_REG_POLARITY1           ((UInt8) 0x09U)
#define TCA6424_REG_POLARITY2           ((UInt8) 0x0AU)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define TCA6424_REG_CONFIG0             ((UInt8) 0x0CU)
#define TCA6424_REG_CONFIG1             ((UInt8) 0x0DU)
#define TCA6424_REG_CONFIG2             ((UInt8) 0x0EU)

/* Input status register */
#define TCA6416_REG_INPUT0              ((UInt8) 0x00U)
#define TCA6416_REG_INPUT1              ((UInt8) 0x01U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define TCA6416_REG_OUTPUT0             ((UInt8) 0x02U)
#define TCA6416_REG_OUTPUT1             ((UInt8) 0x03U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define TCA6416_REG_POLARITY0           ((UInt8) 0x04U)
#define TCA6416_REG_POLARITY1           ((UInt8) 0x05U)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define TCA6416_REG_CONFIG0             ((UInt8) 0x06U)
#define TCA6416_REG_CONFIG1             ((UInt8) 0x07U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief IO expander global driver object.
 */
typedef struct
{
    BspOsal_SemHandle lock;
    /**< Global driver lock. */
} Bsp_IoexpObj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all IO expanders
 */
static Bsp_IoexpObj gBspIoexpObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_ioexpLock(void);
static Int32 Bsp_ioexpUnlock(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for IO expander driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ioexpInit(void)
{
    Int32 retVal = BSP_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspIoexpObj, 0, sizeof (gBspIoexpObj));

    /* Create global lock */
    initValue         = (Int32) 1;
    gBspIoexpObj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspIoexpObj.lock)
    {
        retVal = BSP_EALLOC;
    }

    return (retVal);
}

/**
 *  \brief System de-init for IO expander driver
 *
 *  This API
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ioexpDeInit(void)
{
    if (NULL != gBspIoexpObj.lock)
    {
        /* Delete semaphore's. */
        BspOsal_semDelete(&gBspIoexpObj.lock);
        gBspIoexpObj.lock = NULL;
    }

    return (BSP_SOK);
}

Int32 TCA6424_writeConfig(UInt32       i2cInstId,
                          UInt32       i2cDevAddr,
                          const UInt8 *regValue,
                          UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6424_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] =
            (UInt8) ((UInt32) TCA6424_REG_CONFIG0 | (UInt32) TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6424_writeOutputPort(UInt32       i2cInstId,
                              UInt32       i2cDevAddr,
                              const UInt8 *regValue,
                              UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6424_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] =
            (UInt8) ((UInt32) TCA6424_REG_OUTPUT0 | (UInt32) TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6424_readOutputPort(UInt32 i2cInstId,
                             UInt32 i2cDevAddr,
                             UInt8 *regValue,
                             UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[1U];
    UInt32 tempRegVal32;

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6424_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal32 =
                ((UInt32) TCA6424_REG_OUTPUT0 |
                 (UInt32) TCA6424_CMD_AUTO_INC) + cnt;
            tempRegVal[0U] = (UInt8) tempRegVal32;
            retVal         = Bsp_deviceRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (UInt32) 1U);
            if (BSP_SOK == retVal)
            {
                retVal = Bsp_deviceRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (UInt32) 1U);
            }

            if (BSP_SOK != retVal)
            {
                break;
            }
        }

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6424_readInputPort(UInt32 i2cInstId,
                            UInt32 i2cDevAddr,
                            UInt8 *regValue,
                            UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[1U];
    UInt32 tempRegVal32;

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6424_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal32 =
                ((UInt32) TCA6424_REG_INPUT0 |
                 (UInt32) TCA6424_CMD_AUTO_INC) + cnt;
            /* Set command */
            tempRegVal[0U] = (UInt8) tempRegVal32;
            retVal         = Bsp_deviceRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (UInt32) 1U);
            if (BSP_SOK == retVal)
            {
                retVal = Bsp_deviceRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (UInt32) 1U);
            }

            if (BSP_SOK != retVal)
            {
                break;
            }
        }

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6424_writePolarity(UInt32       i2cInstId,
                            UInt32       i2cDevAddr,
                            const UInt8 *regValue,
                            UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6424_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] =
            (UInt8) ((UInt32) TCA6424_REG_POLARITY0 | (UInt32) TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6416_writeConfig(UInt32       i2cInstId,
                          UInt32       i2cDevAddr,
                          const UInt8 *regValue,
                          UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6416_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] = TCA6416_REG_CONFIG0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6416_writeOutputPort(UInt32       i2cInstId,
                              UInt32       i2cDevAddr,
                              const UInt8 *regValue,
                              UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6416_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] = TCA6416_REG_OUTPUT0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6416_readOutputPort(UInt32 i2cInstId,
                             UInt32 i2cDevAddr,
                             UInt8 *regValue,
                             UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6416_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = TCA6416_REG_OUTPUT0 + (UInt8) cnt;
            retVal         = Bsp_deviceRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (UInt32) 1U);
            if (BSP_SOK == retVal)
            {
                retVal = Bsp_deviceRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (UInt32) 1U);
            }

            if (BSP_SOK != retVal)
            {
                break;
            }
        }

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6416_readInputPort(UInt32 i2cInstId,
                            UInt32 i2cDevAddr,
                            UInt8 *regValue,
                            UInt32 numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6416_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = TCA6416_REG_INPUT0 + (UInt8) cnt;
            retVal         = Bsp_deviceRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (UInt32) 1U);
            if (BSP_SOK == retVal)
            {
                retVal = Bsp_deviceRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (UInt32) 1U);
            }

            if (BSP_SOK != retVal)
            {
                break;
            }
        }

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

Int32 TCA6416_writePolarity(UInt32       i2cInstId,
                            UInt32       i2cDevAddr,
                            const UInt8 *regValue,
                            UInt32       numRegs)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt8  tempRegVal[TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) || (numRegs > TCA6416_NUM_PORTS))
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        Bsp_ioexpLock();

        /* Set command and data */
        tempRegVal[0U] = TCA6416_REG_POLARITY0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = Bsp_deviceRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));

        Bsp_ioexpUnlock();
    }

    return (retVal);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_ioexpLock(void)
{
    BspOsal_semWait(gBspIoexpObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (BSP_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_ioexpUnlock(void)
{
    BspOsal_semPost(gBspIoexpObj.lock);

    return (BSP_SOK);
}

