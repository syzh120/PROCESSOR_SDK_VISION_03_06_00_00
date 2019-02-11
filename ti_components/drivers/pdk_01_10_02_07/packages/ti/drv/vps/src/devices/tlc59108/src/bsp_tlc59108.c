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
 *  \file bsp_tlc59108Api.c
 *
 *  \brief TLC59108 PWM API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <tlc59108/src/bsp_tlc59108Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_tlc59108Lock(void);

static Int32 Bsp_tlc59108UnLock(void);

/**
 *  \brief Sets the PWM register Corresponding to a particular PIN .
 */
static Int32 Bsp_tlc59108SetPwmRegister(UInt32 i2cInstId,
                                        UInt32 tlcDevAdd,
                                        UInt32 pinNum,
                                        UInt8  pwmRegVal);

static Int32 Bsp_tlc59108GetPwmValue(UInt32 dutyCycle, UInt8 *pwmRegVal);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all LCD Ctrl driver
 *  handles.
 */
static Bsp_Tlc59108Obj gBspTlc59108Obj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for TLC59108 driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tlc59108Init(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspTlc59108Obj, 0, sizeof (gBspTlc59108Obj));

    /* Create global LCD Ctrl lock */
    initValue = 1;
    gBspTlc59108Obj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspTlc59108Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    return (retVal);
}

/**
 *  \brief System de-init for TLC59108 driver
 *
 *  This API
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tlc59108DeInit(void)
{
    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspTlc59108Obj.lock);

    return (FVID2_SOK);
}

Int32 Bsp_tlc59108WriteReg(UInt32       i2cInstId,
                           UInt32       tlcDevAdd,
                           const UInt8 *regAddr,
                           const UInt8       *regValue,
                           UInt32       numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check params */
    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  " Tlc59108 - Invalid register write params !!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        retVal = Bsp_deviceWrite8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register write failed !!!\r\n");
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

Int32 Bsp_tlc59108ReadReg(UInt32       i2cInstId,
                          UInt32       tlcDevAdd,
                          const UInt8 *regAddr,
                          UInt8       *regValue,
                          UInt32       numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check params */
    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0))
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  " Tlc59108 - Invalid register Read params !!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        retVal = Bsp_deviceRead8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register read failed !!!\r\n");
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

Int32 Bsp_tlc59108SetPin(UInt32 i2cInstId,
                         UInt32 tlcDevAdd,
                         UInt32 pinNum,
                         UInt32 dutyCycle)
{
    UInt8  bitVal = 0, bitValtmp = 0;
    Int32  retVal = FVID2_SOK;
    UInt8  regVal[2];
    UInt8  regAddr[2];
    UInt32 numRegs   = 0;
    UInt8  pwmRegVal = 0;
    UInt32 regValue = 0;
    UInt32 bitValue = 0;

    if (dutyCycle == 0)
    {
        bitVal = 0x0;
    }
    else if (dutyCycle == 100U)
    {
        bitVal = (UInt8)0x1;
    }
    else if (dutyCycle < 100U)
    {
        bitVal = (UInt8)0x2;
    }
    else
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "In valid dutyCycle \r\n");
        retVal = FVID2_EBADARGS;
    }

    bitValtmp = bitVal;
    Bsp_tlc59108Lock();

    if (retVal == FVID2_SOK)
    {
        regVal[numRegs] = 0U;
        regAddr[numRegs] = BSP_TLC59108_REG_LEDOUT0;
        numRegs++;
        regVal[numRegs] = 0U;
        regAddr[numRegs] = BSP_TLC59108_REG_LEDOUT1;
        numRegs++;

        /* apply the settings */
        retVal = Bsp_deviceRead8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regVal,
            numRegs);

        switch (pinNum)
        {
            case BSP_TLC59108_PIN0:
                /* Read LED0 reg from I2C */
                regValue = ((UInt32)regVal[0] & (~(((UInt32) 0x03U) <<
                             (UInt32) BSP_TLC59108_LEDOUT0_PIN0_SHIFT)));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN0_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN0_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                /* Write this to TLC register via I2C*/
                break;

            case BSP_TLC59108_PIN1:
                regValue = ((UInt32)regVal[0] & ~(((UInt32) 0x03U) <<
                              BSP_TLC59108_LEDOUT0_PIN1_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN1_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN1_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN2:
                regValue = ((UInt32)regVal[0] & ~(((UInt32) 0x03U) <<
                              BSP_TLC59108_LEDOUT0_PIN2_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN2_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN2_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN3:
                regValue = ((UInt32)regVal[0] & ~(((UInt32) 0x03U) <<
                             BSP_TLC59108_LEDOUT0_PIN3_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT0_PIN3_SHIFT) &
                             BSP_TLC59108_LEDOUT0_PIN3_MASK);
                regValue= (regValue | bitValue);
                regVal[0]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN4:
                regValue = ((UInt32)regVal[1] & ~(((UInt32) 0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN4_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN4_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN4_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN5:
                regValue = ((UInt32)regVal[1] & ~(((UInt32) 0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN5_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN5_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN5_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN6:
                regValue = ((UInt32)regVal[1] & ~(((UInt32) 0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN6_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN6_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN6_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            case BSP_TLC59108_PIN7:
                regValue = ((UInt32)regVal[1] & ~(((UInt32) 0x03U) <<
                             BSP_TLC59108_LEDOUT1_PIN7_SHIFT));
                bitValue = (((UInt32)bitVal <<
                             BSP_TLC59108_LEDOUT1_PIN7_SHIFT) &
                             BSP_TLC59108_LEDOUT1_PIN7_MASK);
                regValue= (regValue | bitValue);
                regVal[1]= (UInt8)regValue;
                bitVal= (UInt8)bitValue;
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "In valid Pin Number\n");
                retVal = FVID2_EBADARGS;
                break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (pinNum <= (UInt32) BSP_TLC59108_PIN7)
        {
            /* program regVal[0] into LEDOUT0 register*/
            retVal = Bsp_deviceWrite8(
                i2cInstId,
                tlcDevAdd,
                regAddr,
                regVal,
                numRegs);
        }
        else
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "In valid Pin Number\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if ((bitValtmp == (UInt8)0x2) && (FVID2_SOK == retVal))
    {
        /* if bitval is 0x2 then program the corresponding PWM register as
         * well(get the reg
         * val from the percentage)*/
        retVal = Bsp_tlc59108GetPwmValue(dutyCycle, &pwmRegVal);
        if (retVal == FVID2_SOK)
        {
            retVal = Bsp_tlc59108SetPwmRegister(i2cInstId, tlcDevAdd, pinNum,
                                                pwmRegVal);
        }
    }

    Bsp_tlc59108UnLock();

    return retVal;
}

/**
 *  \brief Sets the PWM register Corresponding to a particular PIN .
 */
static Int32 Bsp_tlc59108SetPwmRegister(UInt32 i2cInstId,
                                        UInt32 tlcDevAdd,
                                        UInt32 pinNum,
                                        UInt8  pwmRegVal)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[1];
    UInt8  regValue[1];
    UInt32 numRegs = 0;

    switch (pinNum)
    {
        case BSP_TLC59108_PIN0:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM0;
            break;
        case BSP_TLC59108_PIN1:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM1;
            break;
        case BSP_TLC59108_PIN2:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM2;
            break;
        case BSP_TLC59108_PIN3:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM3;
            break;
        case BSP_TLC59108_PIN4:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM4;
            break;
        case BSP_TLC59108_PIN5:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM5;
            break;
        case BSP_TLC59108_PIN6:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM6;
            break;
        case BSP_TLC59108_PIN7:
            regAddr[numRegs] = BSP_TLC59108_REG_PWM7;
            break;
        default:
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "In valid Pin Number\n");
            retVal = FVID2_EBADARGS;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        regValue[numRegs] = pwmRegVal;
        numRegs++;

        retVal = Bsp_deviceWrite8(
            i2cInstId,
            tlcDevAdd,
            regAddr,
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " Tlc59108 - I2C register write failed !!!\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Gets the Corresponding PWM register values for duty cycle.
 */
static Int32 Bsp_tlc59108GetPwmValue(UInt32 dutyCycle, UInt8 *pwmRegVal)
{
    Int32 retVal = FVID2_SOK;

    if (dutyCycle >= 100U)
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* 100% ---> 0xFF(255), so approx mul factor is 2.5 */
        *pwmRegVal = (UInt8) ((dutyCycle * 5U) / 2U);
    }

    return (retVal);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_tlc59108Lock(void)
{
    BspOsal_semWait(gBspTlc59108Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_tlc59108UnLock(void)
{
    BspOsal_semPost(gBspTlc59108Obj.lock);

    return (FVID2_SOK);
}

