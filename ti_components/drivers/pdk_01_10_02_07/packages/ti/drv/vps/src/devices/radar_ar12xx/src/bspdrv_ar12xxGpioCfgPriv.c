/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file   bspdrv_ar12xxGpioCfgPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver for GPIO configuration.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_gpio.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Maximum number of instances of GPIO supported by TDA3xx */
#if defined (SOC_TDA3XX)
#define BSP_AR12XX_NUM_GPIO_INST (4U)
#else
#define BSP_AR12XX_NUM_GPIO_INST (8U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Constant list of module base addresses for GPIO */
#if defined (SOC_TDA3XX)
static const UInt32 gGpioModuleAddrList[BSP_AR12XX_NUM_GPIO_INST] =
{
    SOC_GPIO1_BASE,
    SOC_GPIO2_BASE,
    SOC_GPIO3_BASE,
    SOC_GPIO4_BASE
};
#else
static const UInt32 gGpioModuleAddrList[BSP_AR12XX_NUM_GPIO_INST] =
{
    SOC_GPIO1_BASE,
    SOC_GPIO2_BASE,
    SOC_GPIO3_BASE,
    SOC_GPIO4_BASE,
    SOC_GPIO5_BASE,
    SOC_GPIO6_BASE,
    SOC_GPIO7_BASE,
    SOC_GPIO8_BASE
};
#endif
/* Array of devices to which the GPIO Intput Host interrupts are hooked */
static UInt32 gGpioUsed[BSP_AR12XX_NUM_GPIO_INST];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  GPIO interrupt service routine registered. This function will go on
 *          to call the #pHandler registered in the function
 *          #Bsp_ar12xxGpioIntrRegisterCb.
 *
 *  \param  arg     Argument passed from the hardware interrupt handler.
 *
 *  \return None
 */
static void Bsp_ar12xxGpioIsr(UInt32 arg);

/**
 *  \brief  PRCM Enable function to power up the GPIO modules.
 *
 *  \param  instId      GPIO Instance ID.
 *
 *  \return retVal      BSP_SOK if the power is enabled. Other error codes are
 *                      returned in case of failure.
 */
static Int32 Bsp_ar12xxGpioPrcmEnable(UInt32 instId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxGpioInit(const Bsp_ar12xxObj *pObj)
{
    UInt8  gpioInstId, gpioPinNum;
    UInt32 numDevices = pObj->initPrmsCopy.numRadarDevicesInCascade;
    Int32  retVal     = BSP_SOK;
    UInt32 i          = 0U;
    UInt32 j          = 0U;

    /* Loop through the number of devices given and the given input and output
     * GPIO parameters.
     */
    for (i = 0U; i < numDevices; i++)
    {
        /* Configure all the input GPIO pins */
        gpioInstId = pObj->initPrmsCopy.devParams[i].inGpioParams
            [BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId;
        gpioPinNum = pObj->initPrmsCopy.devParams[i].inGpioParams
                     [BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioPinNum;
        if ((gpioPinNum < (UInt8) 32) &&
            (gpioInstId < BSP_AR12XX_NUM_GPIO_INST))
        {
            retVal = Bsp_ar12xxGpioPrcmEnable((UInt32) gpioInstId);
        }
        /* Configure all the output GPIO pins */
        for (j = 0U; j < (UInt32) BSP_AR12XX_GPIO_OUTPUT_COUNT; j++)
        {
            gpioInstId = pObj->initPrmsCopy.devParams[i].outGpioParams[j].gpioInstId;
            gpioPinNum = pObj->initPrmsCopy.devParams[i].outGpioParams[j].gpioPinNum;
            if ((gpioPinNum < (UInt8) 32) &&
                (gpioInstId < BSP_AR12XX_NUM_GPIO_INST))
            {
                retVal = Bsp_ar12xxGpioPrcmEnable((UInt32) gpioInstId);
            }
        }
    }
    for (i = 0; i < BSP_AR12XX_NUM_GPIO_INST; i++)
    {
	gGpioUsed[i] = 0xFFU;
    }
    return retVal;
}

Int32 Bsp_ar12xxGpioPowerOnDeviceCb(rlUInt8_t deviceIndex)
{
    Int32  retVal = BSP_SOK;
    UInt32 i      = 0U;
    UInt32 gpioBase;
    UInt8  gpioPin;

    /* GPIO Direction Setting and initial value */
    for (i = 0U; i < (UInt32) BSP_AR12XX_GPIO_OUTPUT_COUNT; i++)
    {
        if (gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
            outGpioParams[i].gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
        {
            gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[deviceIndex].outGpioParams[i].gpioInstId];
            gpioPin = gBspAr12xxObj.initPrmsCopy.
                devParams[deviceIndex].outGpioParams[i].gpioPinNum;
            GPIOPinWrite((UInt32) gpioBase, (UInt32) gpioPin,
                         (UInt32) GPIO_PIN_LOW);
            GPIODirModeSet((UInt32) gpioBase, (UInt32) gpioPin,
                           (UInt32) GPIO_DIR_OUTPUT);
        }
    }
    BspOsal_sleep(200U);
    if (gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
            outGpioParams[BSP_AR12XX_GPIO_OUTPUT_WARM_RESET].
        gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
    {
        /* Lift the warm reset pin */
        gpioBase =
            gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                devParams[deviceIndex].outGpioParams
                                [BSP_AR12XX_GPIO_OUTPUT_WARM_RESET].gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.
                  devParams[deviceIndex].outGpioParams
                  [BSP_AR12XX_GPIO_OUTPUT_WARM_RESET].gpioPinNum;
        GPIOPinWrite(gpioBase, (UInt32) gpioPin, (UInt32) GPIO_PIN_HIGH);
    }
    if (gBspAr12xxObj.initPrmsCopy.
        devParams[deviceIndex].outGpioParams[BSP_AR12XX_GPIO_OUTPUT_NERRORIN].
        gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
    {
        /* Lift the nErrorIn Pin */
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                       devParams[deviceIndex].outGpioParams[
                                           BSP_AR12XX_GPIO_OUTPUT_NERRORIN].
                                       gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  outGpioParams[BSP_AR12XX_GPIO_OUTPUT_NERRORIN].
                  gpioPinNum;
        GPIOPinWrite(gpioBase, (UInt32) gpioPin, (UInt32) GPIO_PIN_HIGH);
    }
    if (gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].outGpioParams
        [BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO].
        gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
    {
        retVal =
            Bsp_ar12xxGpioConfigSoP(gBspAr12xxObj.initPrmsCopy.sopMode,
                                    deviceIndex);
    }
    if (retVal == BSP_SOK)
    {
        if (gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].outGpioParams
            [BSP_AR12XX_GPIO_OUTPUT_NRESET].
            gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
        {
            /* Lift the nReset signal */
            gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                           devParams[deviceIndex].outGpioParams
                                           [BSP_AR12XX_GPIO_OUTPUT_NRESET].
                                           gpioInstId];
            gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                outGpioParams[BSP_AR12XX_GPIO_OUTPUT_NRESET].gpioPinNum;
            GPIOPinWrite(gpioBase, (UInt32) gpioPin, (UInt32) GPIO_PIN_HIGH);
        }
    }
    return retVal;
}


Int32 Bsp_ar12xxFPDPowerOnDeviceCb(rlUInt8_t deviceIndex)
{
    Int32  retVal = BSP_SOK;
    retVal = BspUtils_appUb960BootAR12xx(gBspAr12xxObj.initPrmsCopy.
                                         devParams[deviceIndex].desPortMap);
    return retVal;
}

Int32 Bsp_ar12xxGpioConfigSoP(UInt32 sopMode, UInt8 deviceIndex)
{
    Int32  retVal = BSP_SOK;
    UInt32 gpioBase;
    UInt8  gpioPin;
    UInt32 syncOut, pmicOut;
    /* Configure the SOP */
    gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[deviceIndex].outGpioParams[
                    BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO].gpioInstId];
    gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].outGpioParams[
        BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO].gpioPinNum;
    GPIOPinWrite(gpioBase, (UInt32) gpioPin, (UInt32) GPIO_PIN_HIGH);

    switch (sopMode)
    {
        case 2U:
            syncOut = GPIO_PIN_HIGH;
            pmicOut = GPIO_PIN_LOW;
            break;
        case 5U:
            syncOut = GPIO_PIN_LOW;
            pmicOut = GPIO_PIN_HIGH;
            break;
        case 4U:
            syncOut = GPIO_PIN_LOW;
            pmicOut = GPIO_PIN_LOW;
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }
    if (retVal == BSP_SOK)
    {
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                        devParams[deviceIndex].outGpioParams
                                       [BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT
                                       ].gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  outGpioParams[BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT].
                  gpioPinNum;
        GPIOPinWrite(gpioBase, (UInt32) gpioPin, syncOut);
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                       devParams[deviceIndex].
                                       outGpioParams
                                       [
                                           BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT
                                       ].gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  outGpioParams[BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT].
                  gpioPinNum;
        GPIOPinWrite(gpioBase, (UInt32) gpioPin, pmicOut);
    }
    return retVal;
}

Int32 Bsp_ar12xxGpioPowerOffDeviceCb(rlUInt8_t deviceIndex)
{
    UInt32 gpioBase;
    UInt8  gpioPin;

    if (gBspAr12xxObj.initPrmsCopy.
        devParams[deviceIndex].outGpioParams[BSP_AR12XX_GPIO_OUTPUT_NRESET].
        gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
    {
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                                       devParams[deviceIndex].
                                       outGpioParams
                                       [BSP_AR12XX_GPIO_OUTPUT_NRESET].
                                       gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  outGpioParams[BSP_AR12XX_GPIO_OUTPUT_NRESET].gpioPinNum;

        /*NRESET Setting*/
        GPIODirModeSet((UInt32) gpioBase, (UInt32) gpioPin,
                       (UInt32) GPIO_DIR_OUTPUT);

        /*Bring the NRESET line Low*/
        GPIOPinWrite((UInt32) gpioBase, (UInt32) gpioPin, (UInt32) GPIO_PIN_LOW);
    }
    return BSP_SOK;
}

Int32 Bsp_ar12xxGpioPinReadCb(rlComIfHdl_t fd)
{
    UInt32 gpioPinValue = 0U;
    Bsp_ar12xxRadarCommHandle commHandle = (Bsp_ar12xxRadarCommHandle) fd;
    UInt32 devIdx = commHandle->deviceIdx;
    UInt32 gpioBase;
    UInt8  gpioPin;

    /* Sleep for 1 ms before reading the GPIO pin */
    BspOsal_sleep(1U);
    if (gBspAr12xxObj.initPrmsCopy.devParams[devIdx].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId
                  < BSP_AR12XX_NUM_GPIO_INST)
    {
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[devIdx].inGpioParams[
                    BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[devIdx].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                  gpioPinNum;
        /* Read the GPIO Pin */
        gpioPinValue = GPIOPinRead((UInt32) gpioBase, (UInt32) gpioPin);
        /* Get to a 1 or 0 value */
        gpioPinValue = (gpioPinValue >> gpioPin) & 0x1U;
    }
    return (Int32) gpioPinValue;
}

Int32 Bsp_ar12xxGpioIntrRegisterCb(UInt8              deviceIndex,
                                   RL_P_EVENT_HANDLER pHandler,
                                   void              *pValue)
{
    UInt32       gpioBase;
    UInt8        gpioPin;
    UInt16       cpuIntrNum;
    UInt32       xBarInst;
    Int32        retVal = BSP_SOK;
#if defined (SOC_TDA3XX)
    /* Constant list of Xbar instance IDs for GPIO */
    const UInt32 gGpioModuleXbarInstId[BSP_AR12XX_NUM_GPIO_INST] =
    {
        (UInt32) GPIO1_IRQ_1,
        (UInt32) GPIO2_IRQ_1,
        (UInt32) GPIO3_IRQ_1,
        (UInt32) GPIO4_IRQ_1
    };
#else
    /* Constant list of Xbar instance IDs for GPIO */
    const UInt32 gGpioModuleXbarInstId[BSP_AR12XX_NUM_GPIO_INST] =
    {
        (UInt32) GPIO1_IRQ_1,
        (UInt32) GPIO2_IRQ_1,
        (UInt32) GPIO3_IRQ_1,
        (UInt32) GPIO4_IRQ_1,
        (UInt32) GPIO5_IRQ_1,
        (UInt32) GPIO6_IRQ_1,
        (UInt32) GPIO7_IRQ_1,
        (UInt32) GPIO8_IRQ_1
    };
#endif

    if (gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
        gpioInstId < BSP_AR12XX_NUM_GPIO_INST)
    {
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                   devParams[deviceIndex].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                                       gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  inGpioParams
                  [BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioPinNum;
        cpuIntrNum = gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR]
                     .
                     cpuIntrIdForGpio;
        xBarInst = gGpioModuleXbarInstId[gBspAr12xxObj.initPrmsCopy.
                    devParams[deviceIndex].inGpioParams
                                         [BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                                         gpioInstId];

        /* Set the GPIO Interrupt Type */
        GPIOIntTypeSet((UInt32) gpioBase, (UInt32) gpioPin,
                       (UInt32) GPIO_INT_TYPE_RISE_EDGE);
        /* Set pin direction as input*/
        GPIODirModeSet((UInt32) gpioBase, (UInt32) gpioPin,
                       (UInt32) GPIO_DIR_INPUT);
        /*Clear interrupt*/
        GPIOPinIntDisable((UInt32) gpioBase, (UInt32) GPIO_INT_LINE_1,
                          (UInt32) gpioPin);
        GPIOPinIntClear((UInt32) gpioBase, (UInt32) GPIO_INT_LINE_1,
                        (UInt32) gpioPin);

        if (pHandler != NULL)
        {
            /*Enable interrupt*/
            GPIOPinIntEnable((UInt32) gpioBase, (UInt32) GPIO_INT_LINE_1,
                             (UInt32) gpioPin);

            /* Register the Interrupt Handler */
            gBspAr12xxObj.radarGpioIntrHandler = pHandler;
            /* Register only one ISR for all device GPIO interrupts */
            if ((gBspAr12xxObj.intrHandle[deviceIndex] == NULL)&&
               (gGpioUsed[gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
               inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId]
               == 0xFFU))
            {
                /* Configure the crossbar */
                BspOsal_irqXbarConnectIrq((UInt32) cpuIntrNum, xBarInst);
                /* Configure the Interrupt */
                BspOsal_clearIntr((UInt32) cpuIntrNum);
                gBspAr12xxObj.intrHandle[deviceIndex] = BspOsal_registerIntr(
                    (UInt32) cpuIntrNum, &Bsp_ar12xxGpioIsr,
                    (void *) NULL);
                gGpioUsed[gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                    inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId] =
                        deviceIndex;
            }
            else
            {
                gBspAr12xxObj.intrHandle[deviceIndex] =
                    gBspAr12xxObj.intrHandle[gGpioUsed[
                        gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                        inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                        gpioInstId]];
            }
        }
        else
        {
            if ((gBspAr12xxObj.intrHandle[deviceIndex] != NULL) &&
               (gGpioUsed[gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
               inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId]
               != 0xFFU))
            {
                /* Configure the crossbar */
                BspOsal_irqXbarDisconnectIrq((UInt32) cpuIntrNum);
                /* Configure the Interrupt */
                BspOsal_clearIntr((UInt32) cpuIntrNum);
                BspOsal_unRegisterIntr(&gBspAr12xxObj.intrHandle[deviceIndex]);
                gBspAr12xxObj.intrHandle[deviceIndex] = NULL;
                gGpioUsed[gBspAr12xxObj.initPrmsCopy.devParams[deviceIndex].
                        inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                        gpioInstId] = 0xFFU;
            }
            else if (gBspAr12xxObj.intrHandle[deviceIndex] != NULL)
            {
                /* Already Unregistered Need to only clear the handle */
                gBspAr12xxObj.intrHandle[deviceIndex] = NULL;
            }
            else
            {
                ; /* Do nothing */
            }
        }
    }
    else
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

void Bsp_ar12xxGpioIRQMaskCb(rlComIfHdl_t fd)
{
    /* This function is dummy because the GPIO interrupt is edge triggered */
    return;
}

void Bsp_ar12xxGpioIRQUnMaskCb(rlComIfHdl_t fd)
{
    /* This function is dummy because the GPIO interrupt is edge triggered */
    return;
}

Int32 Bsp_ar12xxGpioWaitHostIrqLow(rlComIfHdl_t fd, UInt8 highLow)
{
    /* Here we wait in a deadloop to reduce the time taken for reading the
     * status of the host Irq going low.
     */
    UInt32 gpioPinValue = 0U;
    Bsp_ar12xxRadarCommHandle commHandle = (Bsp_ar12xxRadarCommHandle) fd;
    UInt32 devIdx = commHandle->deviceIdx;
    UInt32 gpioBase;
    UInt8  gpioPin;
    int32_t status = BSP_EFAIL;

    if (gBspAr12xxObj.initPrmsCopy.devParams[devIdx].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId
                  < BSP_AR12XX_NUM_GPIO_INST)
    {
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[devIdx].inGpioParams[
                    BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[devIdx].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                  gpioPinNum;
        do
        {
            /* Read the GPIO Pin */
            gpioPinValue = GPIOPinRead((UInt32) gpioBase, (UInt32) gpioPin);
            /* Get to a 1 or 0 value */
            gpioPinValue = (gpioPinValue >> gpioPin) & 0x1U;
        } while (gpioPinValue != (UInt32)highLow);
        status = BSP_SOK;
    }
    else
    {
        status = BSP_EFAIL;
    }
    return status;
}

Int32 Bsp_ar12xxGpioUartSelect(UInt32 devNum)
{
    Int32 retVal = BSP_SOK;
    UInt32 gpioBaseA, gpioBaseB;
    UInt8  gpioPinA, gpioPinB;
    /* Configure the SOP */
    gpioBaseA = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[devNum].outGpioParams[
                    BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA].gpioInstId];
    gpioPinA = gBspAr12xxObj.initPrmsCopy.devParams[devNum].outGpioParams[
        BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA].gpioPinNum;
    gpioBaseB = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.
                    devParams[devNum].outGpioParams[
                    BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB].gpioInstId];
    gpioPinB = gBspAr12xxObj.initPrmsCopy.devParams[devNum].outGpioParams[
        BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB].gpioPinNum;

    if ((gpioBaseA < BSP_AR12XX_NUM_GPIO_INST) && (gpioBaseB < BSP_AR12XX_NUM_GPIO_INST))
    {
        switch (devNum)
        {
           case 0U:
               GPIOPinWrite(gpioBaseA, (UInt32) gpioPinA,0U);
               GPIOPinWrite(gpioBaseB, (UInt32) gpioPinB,0U);
               break;
           case 1U:
               GPIOPinWrite(gpioBaseA, (UInt32) gpioPinA,0U);
               GPIOPinWrite(gpioBaseB, (UInt32) gpioPinB,1U);
               break;
           case 2U:
               GPIOPinWrite(gpioBaseA, (UInt32) gpioPinA,1U);
               GPIOPinWrite(gpioBaseB, (UInt32) gpioPinB,0U);
               break;
           case 3U:
               GPIOPinWrite(gpioBaseA, (UInt32) gpioPinA,1U);
               GPIOPinWrite(gpioBaseB, (UInt32) gpioPinB,1U);
               break;
           default:
               retVal = BSP_EFAIL;
               break;
        }
    }
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void Bsp_ar12xxGpioIsr(UInt32 arg)
{
    UInt32 i          = 0U;
    UInt32 numDevices = gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade;
    UInt32 gpioBase;
    UInt8  gpioPin;

    /* Loop through the number of devices given and find which GPIO has
     * triggered the interrupt.
     */
    for (i = 0U; i < numDevices; i++)
    {
        UInt32 intStatus;
        gpioBase = gGpioModuleAddrList[gBspAr12xxObj.initPrmsCopy.devParams[i].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                                       gpioInstId];
        gpioPin = gBspAr12xxObj.initPrmsCopy.devParams[i].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].gpioPinNum;

        intStatus = GPIOPinIntStatus((UInt32) gpioBase,
                                     /* For now only using Int Line 1 */
                                     (UInt32) GPIO_INT_LINE_1,
                                     (UInt32) gpioPin);

        if (intStatus == (UInt32) ((UInt32) 1U << (UInt32) gpioPin))
        {
            GPIOPinIntClear((UInt32) gpioBase, (UInt32) GPIO_INT_LINE_1,
                            (UInt32) gpioPin);
            BspOsal_clearIntr(gBspAr12xxObj.initPrmsCopy.devParams[i].
                  inGpioParams[BSP_AR12XX_GPIO_INPUT_HOST_INTR].
                              cpuIntrIdForGpio);
            if (gBspAr12xxObj.radarGpioIntrHandler != NULL)
            {
                /* Call the radar link function registered with the device
                 * index.
                 */
                gBspAr12xxObj.radarGpioIntrHandler(i, NULL);
            }
        }
    }
}

static Int32 Bsp_ar12xxGpioPrcmEnable(UInt32 instId)
{
    Int32 retVal = BSP_SOK;
    pmhalPrcmModuleSIdleState_t sIdleState;
#if defined (SOC_TDA3XX)
    /* Constant list of module IDs for GPIO */
    const pmhalPrcmModuleId_t gGpioModuleIdList[BSP_AR12XX_NUM_GPIO_INST] = {
        PMHAL_PRCM_MOD_GPIO1,
        PMHAL_PRCM_MOD_GPIO2,
        PMHAL_PRCM_MOD_GPIO3,
        PMHAL_PRCM_MOD_GPIO4
    };
#else
    /* Constant list of module IDs for GPIO */
    const pmhalPrcmModuleId_t gGpioModuleIdList[BSP_AR12XX_NUM_GPIO_INST] = {
        PMHAL_PRCM_MOD_GPIO1,
        PMHAL_PRCM_MOD_GPIO2,
        PMHAL_PRCM_MOD_GPIO3,
        PMHAL_PRCM_MOD_GPIO4,
        PMHAL_PRCM_MOD_GPIO5,
        PMHAL_PRCM_MOD_GPIO6,
        PMHAL_PRCM_MOD_GPIO7,
        PMHAL_PRCM_MOD_GPIO8,
    };
#endif

    retVal = (Int32) PMHALModuleSIdleStatusGet(gGpioModuleIdList[instId],
                                               &sIdleState);
    if ((retVal == BSP_SOK) &&
        (sIdleState == PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED))
    {
        /* Enable the PRCM for GPIO instance */
        retVal = PMHALModuleModeSet(gGpioModuleIdList[instId],
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
    }
    return retVal;
}



