/*
 *  Copyright (C) 2013 -2017 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file   gpio_v2.c
 *
 * \brief  GPIO Device Abstraction Layer APIs
 *
 *         This file contains the prototypes of the APIs present in the
 *         device abstraction layer file of GPIO.
 *         This also contains some related macros.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_gpio.h>

/* ========================================================================== */
/*                          Function Definitions                             */
/* ========================================================================== */

void GPIOModuleReset(uint32_t baseAdd)
{
    /* Setting the SOFTRESET bit in System Configuration register.
     * Doing so would reset the GPIO module.
     */
    HW_WR_FIELD32(baseAdd + GPIO_SYSCONFIG, GPIO_SYSCONFIG_SOFTRESET,
                  GPIO_SYSCONFIG_SOFTRESET_RESET);

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* GPIO module reset not required */
#else
    /* Waiting until the GPIO Module is reset.*/
    while (GPIO_SYSSTATUS_RESETDONE_INPROGRESS ==
           (HW_RD_FIELD32(baseAdd + GPIO_SYSSTATUS,
                          GPIO_SYSSTATUS_RESETDONE)))
    {
        /* Do nothing - Busy wait */
    }
#endif
}

void GPIOModuleEnable(uint32_t baseAdd)
{
    /* Clearing the DISABLEMODULE bit in the Control(CTRL) register. */
    HW_WR_FIELD32(baseAdd + GPIO_CTRL, GPIO_CTRL_DISABLEMODULE,
                  GPIO_CTRL_DISABLEMODULE_ENABLED);
}

void GPIOModuleDisable(uint32_t baseAdd)
{
    /* Setting the DISABLEMODULE bit in Control(CTRL) register. */
    HW_WR_FIELD32(baseAdd + GPIO_CTRL, GPIO_CTRL_DISABLEMODULE,
                  GPIO_CTRL_DISABLEMODULE_DISABLED);
}

void GPIODirModeSet(uint32_t baseAdd,
                    uint32_t pinNumber,
                    uint32_t pinDirection)
{
    uint32_t gpioOeValue = HW_RD_REG32(baseAdd + GPIO_OE);
    /* Checking if pin is required to be an output pin. */
    if (GPIO_DIR_OUTPUT == pinDirection)
    {
        gpioOeValue &= ~((uint32_t) 1 << pinNumber);
    }
    else
    {
        gpioOeValue |= (uint32_t) 1 << pinNumber;
    }
    HW_WR_REG32(baseAdd + GPIO_OE, gpioOeValue);
}

uint32_t GPIODirModeGet(uint32_t baseAdd,
                        uint32_t pinNumber)
{
    uint32_t retVal = GPIO_DIR_INPUT;

    if ((uint32_t) 0 ==
        (HW_RD_REG32(baseAdd + GPIO_OE) & ((uint32_t) 1 << pinNumber)))
    {
        retVal = GPIO_DIR_OUTPUT;
    }

    return retVal;
}

void GPIOPinWrite(uint32_t baseAdd,
                  uint32_t pinNumber,
                  uint32_t pinValue)
{
    if (GPIO_PIN_HIGH == pinValue)
    {
        HW_WR_REG32(baseAdd + GPIO_SETDATAOUT, (uint32_t) 1 << pinNumber);
    }
    else
    {
        HW_WR_REG32(baseAdd + GPIO_CLEARDATAOUT, (uint32_t) 1 << pinNumber);
    }
}

uint32_t GPIOPinRead(uint32_t baseAdd,
                     uint32_t pinNumber)
{
    return (HW_RD_REG32(baseAdd + GPIO_DATAIN) & ((uint32_t) 1 << pinNumber));
}

uint32_t GPIOPinRead2(uint32_t baseAdd,
                      uint32_t pinNumber)
{
    return (GPIOPinRead(baseAdd, pinNumber) >> pinNumber);
}

void GPIOMultiplePinsWrite(uint32_t baseAdd,
                           uint32_t setMask,
                           uint32_t clrMask)
{
    /* Setting the specified output pins in GPIO_DATAOUT register. */
    HW_WR_REG32(baseAdd + GPIO_SETDATAOUT, setMask);

    /* Clearing the specified output pins in GPIO_DATAOUT register. */
    HW_WR_REG32(baseAdd + GPIO_CLEARDATAOUT, clrMask);
}

uint32_t GPIOMultiplePinsRead(uint32_t baseAdd,
                              uint32_t readMask)
{
    return (HW_RD_REG32(baseAdd + GPIO_DATAIN) & readMask);
}

void GPIOPinIntEnable(uint32_t baseAdd,
                      uint32_t intLine,
                      uint32_t pinNumber)
{
    if (GPIO_INT_LINE_1 == intLine)
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_SET_0, (uint32_t) 1 << pinNumber);
    }
    else
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_SET_1, (uint32_t) 1 << pinNumber);
    }
}

void GPIOPinIntDisable(uint32_t baseAdd,
                       uint32_t intLine,
                       uint32_t pinNumber)
{
    if (GPIO_INT_LINE_1 == intLine)
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_CLR_0, (uint32_t) 1 << pinNumber);
    }
    else
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_CLR_1, (uint32_t) 1 << pinNumber);
    }
}

void GPIOIntTypeSet(uint32_t baseAdd,
                    uint32_t pinNumber,
                    uint32_t eventType)
{
    uint32_t gpioValue0, gpioValue1;
    eventType &= (uint32_t) 0xFFU;

    switch (eventType)
    {
        case GPIO_INT_TYPE_NO_LEVEL:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT0);
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT1);

            /* Disabling logic LOW level detect interrupt generation. */
            gpioValue0 &= ~((uint32_t) 1 << pinNumber);
            /* Disabling logic HIGH level detect interrupt generation. */
            gpioValue1 &= ~((uint32_t) 1 << pinNumber);

            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT0, gpioValue0);
            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT1, gpioValue1);
            break;

        case GPIO_INT_TYPE_LEVEL_LOW:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT0);

            /* Enabling logic LOW level detect interrupt geenration. */
            gpioValue0 |= (uint32_t) 1 << pinNumber;

            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT0, gpioValue0);
            break;

        case GPIO_INT_TYPE_LEVEL_HIGH:
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT1);

            /* Enabling logic HIGH level detect interrupt generation. */
            gpioValue1 |= (uint32_t) 1 << pinNumber;

            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT1, gpioValue1);
            break;

        case GPIO_INT_TYPE_BOTH_LEVEL:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT0);
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_LEVELDETECT1);

            /* Enabling logic LOW level detect interrupt geenration. */
            gpioValue0 |= (uint32_t) 1 << pinNumber;
            /* Enabling logic HIGH level detect interrupt generation. */
            gpioValue1 |= (uint32_t) 1 << pinNumber;

            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT0, gpioValue0);
            HW_WR_REG32(baseAdd + GPIO_LEVELDETECT1, gpioValue1);
            break;

        case GPIO_INT_TYPE_NO_EDGE:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_RISINGDETECT);
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_FALLINGDETECT);

            /* Disabling rising edge detect interrupt generation. */
            gpioValue0 &= ~((uint32_t) 1 << pinNumber);
            /* Disabling falling edge detect interrupt generation. */
            gpioValue1 &= ~((uint32_t) 1 << pinNumber);

            HW_WR_REG32(baseAdd + GPIO_RISINGDETECT, gpioValue0);
            HW_WR_REG32(baseAdd + GPIO_FALLINGDETECT, gpioValue1);
            break;

        case GPIO_INT_TYPE_RISE_EDGE:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_RISINGDETECT);

            /* Enabling rising edge detect interrupt generation. */
            gpioValue0 |= (uint32_t) 1 << pinNumber;

            HW_WR_REG32(baseAdd + GPIO_RISINGDETECT, gpioValue0);
            break;

        case GPIO_INT_TYPE_FALL_EDGE:
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_FALLINGDETECT);

            /* Enabling falling edge detect interrupt generation. */
            gpioValue1 |= (uint32_t) 1 << pinNumber;

            HW_WR_REG32(baseAdd + GPIO_FALLINGDETECT, gpioValue1);
            break;

        case GPIO_INT_TYPE_BOTH_EDGE:
            gpioValue0 = HW_RD_REG32(baseAdd + GPIO_RISINGDETECT);
            gpioValue1 = HW_RD_REG32(baseAdd + GPIO_FALLINGDETECT);

            /* Enabling rising edge detect interrupt generation. */
            gpioValue0 |= (uint32_t) 1 << pinNumber;

            /* Enabling falling edge detect interrupt generation. */
            gpioValue1 |= (uint32_t) 1 << pinNumber;
            HW_WR_REG32(baseAdd + GPIO_RISINGDETECT, gpioValue0);
            HW_WR_REG32(baseAdd + GPIO_FALLINGDETECT, gpioValue1);

            break;

        default:
            break;
    }
}

uint32_t GPIOIntTypeGet(uint32_t baseAdd,
                        uint32_t pinNumber)
{
    uint32_t intEvent =
        (GPIO_INT_TYPE_NO_LEVEL | GPIO_INT_TYPE_NO_EDGE);

    /* Checking if logic LOW level trigger interrupt is enabled. */
    if ((uint32_t) 0 !=
        (HW_RD_REG32(baseAdd + GPIO_LEVELDETECT0) & ((uint32_t) 1 << pinNumber)))
    {
        intEvent &= ~GPIO_INT_TYPE_NO_LEVEL;
        intEvent |= GPIO_INT_TYPE_LEVEL_LOW;
    }

    /* Checking if logic HIGH level trigger interrupt is enabled. */
    if ((uint32_t) 0 !=
        (HW_RD_REG32(baseAdd + GPIO_LEVELDETECT1) & ((uint32_t) 1 << pinNumber)))
    {
        intEvent &= ~GPIO_INT_TYPE_NO_LEVEL;
        intEvent |= GPIO_INT_TYPE_LEVEL_HIGH;
    }

    /* Checking if rising edge trigger interrupt is enabled. */
    if ((uint32_t) 0 !=
        (HW_RD_REG32(baseAdd + GPIO_RISINGDETECT) & ((uint32_t) 1 << pinNumber)))
    {
        intEvent &= ~GPIO_INT_TYPE_NO_EDGE;
        intEvent |= GPIO_INT_TYPE_RISE_EDGE;
    }

    /* Checking if falling edge trigger interrupt is enabled. */
    if ((uint32_t) 0 !=
        (HW_RD_REG32(baseAdd + GPIO_FALLINGDETECT) & ((uint32_t) 1 << pinNumber)))
    {
        intEvent &= ~GPIO_INT_TYPE_NO_EDGE;
        intEvent |= GPIO_INT_TYPE_FALL_EDGE;
    }

    return intEvent;
}

uint32_t GPIOPinIntStatus(uint32_t baseAdd,
                          uint32_t intLine,
                          uint32_t pinNumber)
{
    uint32_t intStatus = 0;

    if (GPIO_INT_LINE_1 == intLine)
    {
        intStatus =
            HW_RD_REG32(baseAdd +
                        GPIO_IRQSTATUS_0) & ((uint32_t) 1 << pinNumber);
    }
    else
    {
        intStatus =
            HW_RD_REG32(baseAdd +
                        GPIO_IRQSTATUS_1) & ((uint32_t) 1 << pinNumber);
    }

    return intStatus;
}

void GPIOPinIntClear(uint32_t baseAdd,
                     uint32_t intLine,
                     uint32_t pinNumber)
{
    if (GPIO_INT_LINE_1 == intLine)
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_0, (uint32_t) 1 << pinNumber);
    }
    else
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_1, (uint32_t) 1 << pinNumber);
    }
}

uint32_t GPIORawIntStatus(uint32_t baseAdd,
                          uint32_t intLine,
                          uint32_t readMask)
{
    uint32_t intStatus = 0;

    if (GPIO_INT_LINE_1 == intLine)
    {
        intStatus = HW_RD_REG32(baseAdd + GPIO_IRQSTATUS_RAW_0) & readMask;
    }
    else
    {
        intStatus = HW_RD_REG32(baseAdd + GPIO_IRQSTATUS_RAW_1) & readMask;
    }

    return intStatus;
}

void GPIOTriggerPinInt(uint32_t baseAdd,
                       uint32_t intLine,
                       uint32_t pinNumber)
{
    if (GPIO_INT_LINE_1 == intLine)
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_RAW_0, (uint32_t) 1 << pinNumber);
    }
    else
    {
        HW_WR_REG32(baseAdd + GPIO_IRQSTATUS_RAW_1, (uint32_t) 1 << pinNumber);
    }
}

void GPIOWakeupGlobalEnable(uint32_t baseAdd)
{
    /* Setting the ENAWAKEUP bit in SYSCONFIG register. */
    HW_WR_FIELD32(baseAdd + GPIO_SYSCONFIG, GPIO_SYSCONFIG_ENAWAKEUP,
                  GPIO_SYSCONFIG_ENAWAKEUP_ENABLE);
}

void GPIOWakeupGlobalDisable(uint32_t baseAdd)
{
    /* Clearing the ENAWAKEUP bit in SYSCONFIG register. */
    HW_WR_FIELD32(baseAdd + GPIO_SYSCONFIG, GPIO_SYSCONFIG_ENAWAKEUP,
                  GPIO_SYSCONFIG_ENAWAKEUP_DISABLE);
}

void GPIOPinIntWakeUpEnable(uint32_t baseAdd,
                            uint32_t swakeupLine,
                            uint32_t pinNumber)
{
    uint32_t gpioRegValue;
    if (GPIO_INT_LINE_1 == swakeupLine)
    {
        gpioRegValue  = HW_RD_REG32(baseAdd + GPIO_IRQWAKEN_0);
        gpioRegValue |= (uint32_t) 1 << pinNumber;
        HW_WR_REG32(baseAdd + GPIO_IRQWAKEN_0, gpioRegValue);
    }
    else
    {
        gpioRegValue  = HW_RD_REG32(baseAdd + GPIO_IRQWAKEN_1);
        gpioRegValue |= (uint32_t) 1 << pinNumber;
        HW_WR_REG32(baseAdd + GPIO_IRQWAKEN_1, gpioRegValue);
    }
}

void GPIOPinIntWakeUpDisable(uint32_t baseAdd,
                             uint32_t swakeupLine,
                             uint32_t pinNumber)
{
    uint32_t gpioRegValue;
    if (GPIO_INT_LINE_1 == swakeupLine)
    {
        gpioRegValue  = HW_RD_REG32(baseAdd + GPIO_IRQWAKEN_0);
        gpioRegValue &= ~((uint32_t) 1 << pinNumber);
        HW_WR_REG32(baseAdd + GPIO_IRQWAKEN_0, gpioRegValue);
    }
    else
    {
        gpioRegValue  = HW_RD_REG32(baseAdd + GPIO_IRQWAKEN_1);
        gpioRegValue &= ~((uint32_t) 1 << pinNumber);
        HW_WR_REG32(baseAdd + GPIO_IRQWAKEN_1, gpioRegValue);
    }
}

void GPIOAutoIdleModeControl(uint32_t baseAdd, uint32_t modeFlag)
{
    /* Programming the AUTOIDLE bit in System Configuration Register. */
    HW_WR_FIELD32(baseAdd + GPIO_SYSCONFIG, GPIO_SYSCONFIG_AUTOIDLE, modeFlag);
}

void GPIOIdleModeConfigure(uint32_t baseAdd,
                           uint32_t modeFlag)
{
    /* Programming the IDLEMODE field in System Configuration Register. */
    HW_WR_FIELD32(baseAdd + GPIO_SYSCONFIG, GPIO_SYSCONFIG_IDLEMODE, modeFlag);
}

void GPIOGatingRatioConfigure(uint32_t baseAdd,
                              uint32_t configFlag)
{
    /* Programming the GATINGRATIO field in GPIO_CTRL register. */
    HW_WR_FIELD32(baseAdd + GPIO_CTRL, GPIO_CTRL_GATINGRATIO, configFlag);
}

void GPIODebounceFuncControl(uint32_t baseAdd,
                             uint32_t pinNumber,
                             uint32_t controlFlag)
{
    uint32_t gpioRegValue = HW_RD_REG32(baseAdd + GPIO_DEBOUNCENABLE);
    /* Clearing the DEBOUNCEENABLE[n] bit in GPIO_DEBOUNCEENABLE register. */
    gpioRegValue &= ~((uint32_t) 1 << pinNumber);

    /* Programming the DEBOUNCEENABLE[n] bit in GPIO_DEBOUNCEENABLE register.*/
    gpioRegValue |= controlFlag << pinNumber;
    HW_WR_REG32(baseAdd + GPIO_DEBOUNCENABLE, gpioRegValue);
}

void GPIODebounceTimeConfig(uint32_t baseAdd,
                            uint32_t debounceTime)
{
    /* Programming the DEBOUNCETIME field in GPIO_DEBOUNCINGTIME register. */
    HW_WR_REG32(baseAdd + GPIO_DEBOUNCINGTIME, debounceTime &
                GPIO_DEBOUNCINGTIME_DEBOUNCETIME_MASK);
}

uint32_t GPIORevisionInfoGet(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + GPIO_REVISION));
}

void GPIOIntrClearMask(uint32_t baseAddr, uint32_t intrLine, uint32_t pinMask)
{
    if (GPIO_INT_LINE_1 == intrLine)
    {
        /* Clear the interrupt status of specified gpio pin */
        HW_WR_REG32((baseAddr + GPIO_IRQSTATUS_0), (pinMask));
    }
    else
    {
        /* Clear the interrupt status of specified gpio pin */
        HW_WR_REG32((baseAddr + GPIO_IRQSTATUS_1), (pinMask));
    }
}

uint32_t GPIOPinOutValueRead(uint32_t baseAddr, uint32_t pinNumber)
{
    return((HW_RD_REG32(baseAddr + GPIO_DATAOUT)) & (((uint32_t)1U) << pinNumber));
}

/******************************* End Of File ********************************/
