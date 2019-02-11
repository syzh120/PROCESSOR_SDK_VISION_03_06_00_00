/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file bspdrv_lcdCtrlApi.c
 *
 *  \brief LCDCTRL(LCD controller) FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <lcdCtrl/src/bspdrv_lcdCtrlPriv.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>

#if defined(SOC_AM574x) || defined(SOC_AM572x) || defined(SOC_AM571x)
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/src/ip/ecap/V0/ecap.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief I2C address of the STM touch screen used in 10-inch LCD board. */
#define LCDCTRL_STM_TOUCH_I2C_ADDR0                 (0x18U)

/** \brief I2C address of the STM touch screen used in 7-inch LCD board. */
#define LCDCTRL_ATMXT224_TOUCH_I2C_ADDR0            (0x4AU)

/** \brief I2C address of the Parallel port to MIPI DSI TC358778 in
 *         OSD 1080p LCD board. */
#define LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0         (0x0EU)

/** \brief I2C address of the ioexp used to power on OSD 1080P LCD board */
#define LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0    (0x27U)

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)

/** \brief I2C address of LCD module for OSD LCD */
#define LCDCTRL_OSD070T1718_LCD_MODULE_I2C_ADDR0    (0x50U)

/** \brief I2C address of touch connector for OSD070T1718 LCD */
#define LCDCTRL_OSD070T1718_TOUCH_I2C_ADDR0         (0x5CU)

/** \brief I2C address of touch connector for OSD101T2587 LCD */
#define LCDCTRL_OSD101T2587_TOUCH_I2C_SLAVE_ADDR0   (0x38U)

/** \brief chip id regiser of touch connector for OSD101T2587 LCD */
#define LCDCTRL_OSD101T2587_ID_G_CIPHER             (0xA3U)

#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Fdrv_Handle Bsp_lcdCtrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 Bsp_lcdCtrlDelete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 Bsp_lcdCtrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
static Bsp_LcdCtrlHandleObj *Bsp_lcdCtrlAllocObj(void);

static Int32 Bsp_lcdCtrlFreeObj(Bsp_LcdCtrlHandleObj *pObj);

static Int32 Bsp_lcdCtrlLockObj(Bsp_LcdCtrlHandleObj *pObj);

static Int32 Bsp_lcdCtrlUnlockObj(Bsp_LcdCtrlHandleObj *pObj);

static Int32 Bsp_lcdCtrlLock(void);

static Int32 Bsp_lcdCtrlUnlock(void);

static Int32 Bsp_lcdCtrlPowerOnOff(const Bsp_LcdCtrlHandleObj *pObj, Bool flag);

static Int32 Bsp_lcdCtrlBackLightCtrl(const Bsp_LcdCtrlHandleObj *pObj,
                                      Bool                        flag);

static Int32 Bsp_lcdCtrlSetBrightness(const Bsp_LcdCtrlHandleObj *pObj,
                                      const UInt32               *brightVal);

static Int32 Bsp_lcdCtrlSelectMode(const Bsp_LcdCtrlHandleObj *pObj,
                                   const UInt32               *mode);
static Int32 Bsp_lcdCtrlGetPanelInfo(const Bsp_LcdCtrlHandleObj *pObj,
                                     Bsp_LcdCtrlPanelInfo       *panelInfo);

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
static Int32 Bsp_lcdCtrlBackLightCtrlOSD070T1718(UInt32 dutyCycle);
static Int32 Bsp_lcdCtrlBackLightCtrlOSD101T2045(UInt32 dutyCycle);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief TVP5158 driver function pointer. */
static const Fvid2_DrvOps gBspLcdCtrlDrvOps =
{
    FVID2_LCD_CTRL_DRV,         /* Driver ID */
    &Bsp_lcdCtrlCreate,         /* Create */
    &Bsp_lcdCtrlDelete,         /* Delete */
    &Bsp_lcdCtrlControl,        /* Control */
    NULL,                       /* Queue */
    NULL,                       /* Dequeue */
    NULL,                       /* ProcessFrames */
    NULL,                       /* GetProcessedFrames */
    NULL,                       /* ProcessRequest */
    NULL                        /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all LCDCTRL driver
 *  handles.
 */
static Bsp_LcdCtrlObj     gBspLcdCtrlObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for LCDCTRL driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_lcdCtrlInit(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspLcdCtrlObj, 0, sizeof (gBspLcdCtrlObj));

    /* Create global TVP5158 lock */
    initValue           = 1;
    gBspLcdCtrlObj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspLcdCtrlObj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        /* Register LCD Controller driver with FVID2 sub-system */
        retVal = Fvid2_registerDriver(&gBspLcdCtrlDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspLcdCtrlObj.lock);
        }
    }

    Bsp_tlc59108Init();

    return (retVal);
}

/**
 *  \brief System de-init for TVP5158 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_lcdCtrlDeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspLcdCtrlDrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspLcdCtrlObj.lock);

    Bsp_tlc59108DeInit();

    return (FVID2_SOK);
}

/**
 *  \brief LCDCTRL create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the LCDCTRL is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  LCD Controller.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          FVID2_LCD_CTRL_DRV.
 *  \param instId           [IN] Must be 0. TODO - Check
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_LcdCtrlCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] LCDCTRL driver return parameter -
 *                          pointer to Bsp_LcdCtrlCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the retVal information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_lcdCtrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_LcdCtrlHandleObj    *pObj = NULL;
    Bsp_LcdCtrlCreateParams *lcdCtrlCreatePrms;
    Bsp_LcdCtrlCreateStatus *lcdCtrlCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        (drvId != FVID2_LCD_CTRL_DRV) ||
        (instId != 0U))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        lcdCtrlCreatePrms = (Bsp_LcdCtrlCreateParams *) createPrms;
        if (lcdCtrlCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate driver handle */
        pObj = Bsp_lcdCtrlAllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            lcdCtrlCreatePrms,
            sizeof (*lcdCtrlCreatePrms));
    }

    /* Fill the retVal if possible */
    if (NULL != createStatusArgs)
    {
        lcdCtrlCreateStatus =
            (Bsp_LcdCtrlCreateStatus *) createStatusArgs;
        lcdCtrlCreateStatus->retVal = retVal;
    }

    return (pObj);
}

/**
 *  \brief Delete function that is called when Fvid2_delete is called.
 *
 *  This API
 *      - free's driver handle object
 *
 *  \param handle           [IN] Driver handle.
 *  \param deleteArgs       [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code. *
 */
static Int32 Bsp_lcdCtrlDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_LcdCtrlHandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_LcdCtrlHandleObj *) handle;
        retVal = Bsp_lcdCtrlFreeObj(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Control API that gets called when Fvid2_control is called.
 *
 *  This API does handle level semaphore locking
 *
 *  \param handle           [IN] LCDCTRL driver handle returned by
 *                          create function.
 *  \param cmd              [IN] Supports the LCD controller interface
 *                          commands.
 *  \param cmdArgs          [IN] Depending on the command this will vary.
 *  \param cmdStatusArgs    [OUT] Depending on the command this will vary.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error codes for illegal parameters and
 *                          I2C command RX/TX error.
 */
static Int32 Bsp_lcdCtrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_LcdCtrlHandleObj *pObj = NULL;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pObj = (Bsp_LcdCtrlHandleObj *) handle;

        /* lock handle */
        Bsp_lcdCtrlLockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_LCDCTRL_POWER_ON:
                retVal = Bsp_lcdCtrlPowerOnOff(pObj, (Bool) TRUE);
                break;

            case IOCTL_BSP_LCDCTRL_POWER_OFF:
                retVal = Bsp_lcdCtrlPowerOnOff(pObj, FALSE);
                break;

            case IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT:
                retVal = Bsp_lcdCtrlBackLightCtrl(pObj, (Bool) TRUE);
                break;

            case IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT:
                retVal = Bsp_lcdCtrlBackLightCtrl(pObj, FALSE);
                break;

            case IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS:
                retVal = Bsp_lcdCtrlSetBrightness(
                    pObj,
                    (UInt32 *) cmdArgs);
                break;

            case IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC:
                retVal = Bsp_lcdCtrlSelectMode(
                    pObj,
                    (UInt32 *) cmdArgs);
                break;

            case IOCTL_BSP_LCDCTRL_GET_PANEL_INFO:
                retVal = Bsp_lcdCtrlGetPanelInfo(
                    pObj,
                    (Bsp_LcdCtrlPanelInfo *) cmdArgs);
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_lcdCtrlUnlockObj(pObj);
    }

    return (retVal);
}

static Int32 Bsp_lcdCtrlPowerOnOff(const Bsp_LcdCtrlHandleObj *pObj, Bool flag)
{
    Int32  retVal = FVID2_SOK;
    UInt32 dutyCycle;
    UInt8  regAddr[2];
    UInt8  regValue[2], ledOut1;
    UInt32 numRegs;
    UInt8  pcf8575RegVal[2];

    if ((Bool) TRUE == flag)
    {
        numRegs = 0;

        regAddr[numRegs]  = BSP_TLC59108_REG_MODE1;
        regValue[numRegs] = 0x00; /* TODO Check this value */
        numRegs++;

        Bsp_tlc59108WriteReg(pObj->createPrms.deviceI2cInstId,
                             pObj->createPrms.deviceI2cAddr[
                                 BSP_LCDCTRL_TLC59108_INST_0],
                             &regAddr[0],
                             &regValue[0],
                             numRegs);

        /* Detect ATMXT224 first as this is unique. Detecting STM present
         * in 10-inch LCD results in false detect in Tda2xx EVM. */
        retVal = Bsp_deviceI2cProbeDevice(
            pObj->createPrms.deviceI2cInstId,
            (UInt8) LCDCTRL_ATMXT224_TOUCH_I2C_ADDR0);
        if (FVID2_SOK == retVal)
        {
            /* This is for 7-Inch LCD, bit 8 for this LCD will contorl the
             * mirror image settings here we configure it to display normal
             * Image only.  */
            ledOut1 = (UInt8) 0x11;

            /* After probing ATMXT224 in 7-inch LCD, immediate access to TLC
             * will lead to I2C Bus Busy, so adding 5ms Delay.
             */
            BspOsal_sleep((UInt32) 5);
        }
        else
        {
            retVal = Bsp_deviceI2cProbeDevice(
                pObj->createPrms.deviceI2cInstId,
                LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0);
            if (FVID2_SOK == retVal)
            {
                /* Drive P0 of ioexp to low to turn on the power to TC358778
                 * Parallael to Mipi DSI chip on OSD 1080P LCD board
                 */
                retVal = Bsp_deviceRawRead8(
                    pObj->createPrms.deviceI2cInstId,
                    LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0,
                    pcf8575RegVal,
                    2U);
                if (retVal == FVID2_SOK)
                {
                    pcf8575RegVal[0] = pcf8575RegVal[0] & (UInt8) 0xFE;
                    retVal           = Bsp_deviceRawWrite8(
                        pObj->createPrms.deviceI2cInstId,
                        LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0,
                        pcf8575RegVal,
                        2U);
                }
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(
                        BspDeviceTrace, GT_ERR,
                        "Powering on TC358778 on OSD 1080P LCD board failed\r\n");
                }
                ledOut1 = (UInt8) 0x10;
            }
            else
            {
                /* For 10 -inch LG LCD panel, the bit 8 of TLC specified the
                 * pixel polarity at which data should be sampled - configuring
                 * it torising edge as there is a inverter in LCD.
                 */
                ledOut1 = (UInt8) 0x51;
            }
        }

        /* initial setup - done during power on of LCD board */
        numRegs           = 0;
        regAddr[numRegs]  = BSP_TLC59108_REG_LEDOUT0;
        regValue[numRegs] = 0x00;
        numRegs++;

        regAddr[numRegs]  = BSP_TLC59108_REG_LEDOUT1;
        regValue[numRegs] = ledOut1;
        numRegs++;

        Bsp_tlc59108WriteReg(pObj->createPrms.deviceI2cInstId,
                             pObj->createPrms.deviceI2cAddr[
                                 BSP_LCDCTRL_TLC59108_INST_0],
                             &regAddr[0],
                             &regValue[0],
                             numRegs);

        dutyCycle = 0; /* TODO - Check if this value is fine*/
    }
    else
    {
        /* For OSD 1080P LCD display power off the board by
         * driving high P0 port of PCF 8575. */
        retVal = Bsp_deviceI2cProbeDevice(
            pObj->createPrms.deviceI2cInstId,
            LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0);
        if (FVID2_SOK == retVal)
        {
            /* Drive P0 of ioexp to high to turn off the power to TC358778
             * Parallael to Mipi DSI chip on OSD 1080P LCD board
             */
            retVal = Bsp_deviceRawRead8(
                pObj->createPrms.deviceI2cInstId,
                LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0,
                pcf8575RegVal,
                2U);
            if (retVal == FVID2_SOK)
            {
                pcf8575RegVal[0] = pcf8575RegVal[0] | (UInt8) 0x01;
                retVal           = Bsp_deviceRawWrite8(
                    pObj->createPrms.deviceI2cInstId,
                    LCDCTRL_PCF8575_MIPI_DSI_PWRON_I2C_ADDR0,
                    pcf8575RegVal,
                    2U);
            }
            if (retVal != FVID2_SOK)
            {
                GT_0trace(
                    BspDeviceTrace, GT_ERR,
                    "Powering off TC358778 on OSD 1080P LCD board failed\r\n");
            }
        }
        dutyCycle = 100U;
    }

    retVal = Bsp_tlc59108SetPin(pObj->createPrms.deviceI2cInstId,
                                pObj->createPrms.deviceI2cAddr[
                                    BSP_LCDCTRL_TLC59108_INST_0],
                                BSP_LCDCTRL_THREEFIVE_AVDD_EN,
                                dutyCycle);

    return retVal;
}

static Int32 Bsp_lcdCtrlBackLightCtrl(const Bsp_LcdCtrlHandleObj *pObj,
                                      Bool                        flag)
{
    Int32  retVal = FVID2_SOK;
    UInt32 dutyCycle;
    UInt32 isOsd1080pLcd = (UInt32)FALSE;
    UInt32 peripheralCmdOn = (UInt32) FALSE;
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    UInt32 isOsdWvgaLcd  = (UInt32)FALSE;
    UInt8  regValue = (UInt8) 0U, regAddr;
#endif

    if ((Bool) TRUE == flag)
    {
        dutyCycle = 100U;
    }
    else
    {
        dutyCycle = 0;
    }

    retVal = Bsp_deviceI2cProbeDevice(
        pObj->createPrms.deviceI2cInstId,
        (UInt8) LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0);
    if (retVal == FVID2_SOK)
    {
        isOsd1080pLcd = (UInt32)TRUE;
    }

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    retVal = Bsp_deviceI2cProbeDevice(
        pObj->createPrms.deviceI2cInstId,
        (UInt8) LCDCTRL_OSD070T1718_LCD_MODULE_I2C_ADDR0);
    if (retVal == FVID2_SOK)
    {
        isOsdWvgaLcd = (UInt32)TRUE;
    }
#endif

    if (isOsd1080pLcd == (UInt32)FALSE)
    {
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        if (TRUE == isOsdWvgaLcd)
        {
            retVal = Bsp_lcdCtrlBackLightCtrlOSD070T1718(dutyCycle);
        }
        else
        {
#endif
            retVal = Bsp_tlc59108SetPin(pObj->createPrms.deviceI2cInstId,
                                    pObj->createPrms.deviceI2cAddr[
                                        BSP_LCDCTRL_TLC59108_INST_0],
                                    BSP_LCDCTRL_THREEFIVE_ENBKL,
                                    dutyCycle);
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        }
#endif
    }
    else
    {
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        /* This needs to be AM572x/AM574x IDK EVM driving back light from ECAP */
        retVal = Bsp_lcdCtrlBackLightCtrlOSD101T2045(dutyCycle);

        /* AM572x/AM574x IDK boards support two different LCD types
         * OSD101T2045-53TS and OSD101T2587-53TS
         * both LCD displays initialization is common,
         * except Turn on Peripheral command is needed for OSD101T2587-53TS.
         *
         * Detection mechanism between two LCDs is to use the capacitive touch
         * controller to determine the panel type since each panel uses a
         * different controller.
         * If the controller is not connected then it should be assumed that
         * the OSD101T2587-53TS panel is connected. */

        regAddr = (UInt8) LCDCTRL_OSD101T2587_ID_G_CIPHER; /* ID_G_CIPHER, Chip vendor ID */
        retVal  = Bsp_deviceRead8(
                             pObj->createPrms.deviceI2cInstId,
                            (UInt32)LCDCTRL_OSD101T2587_TOUCH_I2C_SLAVE_ADDR0, /* Capacitive touch i2c slave address */
                             &regAddr,
                             &regValue,
                             (UInt32) 1U);
        if (retVal == FVID2_SOK)
        {
            /* 0x54 is the Chip Vendor ID of capacitive touch OSD101T2587-53TS */
            if (regValue == ((UInt8) 0x54U))
            {
                peripheralCmdOn = (UInt32) TRUE;
            }
        }
        else
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      " OSD101T2587/2045 - I2C register read failed !!!\r\n Please check if LCD module is connected to the board !!!\r\n");
        }
#else
        retVal = Bsp_tlc59108SetPin(pObj->createPrms.deviceI2cInstId,
                          pObj->createPrms.deviceI2cAddr[
                            BSP_LCDCTRL_TLC59108_INST_0],
                          BSP_LCDCTRL_THREEFIVE_PWM,
                          dutyCycle);
#endif
        if (flag == TRUE)
        {
            Tc358778_lcdBridgeInit(pObj->createPrms.deviceI2cInstId,
                               LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0, peripheralCmdOn);
        }
        else
        {
            Tc358778_lcdBridgeDeinit(pObj->createPrms.deviceI2cInstId,
                                LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0);
        }
    }

    return retVal;
}

static Int32 Bsp_lcdCtrlSetBrightness(const Bsp_LcdCtrlHandleObj *pObj,
                                      const UInt32               *brightVal)
{
    Int32  retVal = FVID2_SOK;
    Int32  probeVal;
    UInt32 isOsd1080pLcd = (UInt32)FALSE;

    if (brightVal == NULL)
    {
        /* G0trace(BspDeviceTrace, GT_ERR,
         *        " Tlc59108 - NULL Arguments" */
        retVal = FVID2_EBADARGS;
    }

    if (retVal == FVID2_SOK)
    {
        if (*brightVal > 100U)
        {
            retVal = FVID2_EBADARGS;
        }
    }

    if (retVal == FVID2_SOK)
    {
        /* For OSD 1080P display make the dutycycle as 100 */
        /* Probe Parallel port to MIPI DSI TC358778 chip @ 0x0E.
         * if found it is OSD 1080P LCD */
        probeVal = Bsp_deviceI2cProbeDevice(
            pObj->createPrms.deviceI2cInstId,
            (UInt8) LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0);
        if (probeVal == FVID2_SOK)
        {
            isOsd1080pLcd = (UInt32)TRUE;
        }
    }

    if ((retVal == FVID2_SOK) && (isOsd1080pLcd == (UInt32)FALSE))
    {
        retVal = Bsp_tlc59108SetPin(pObj->createPrms.deviceI2cInstId,
                                    pObj->createPrms.deviceI2cAddr[
                                        BSP_LCDCTRL_TLC59108_INST_0],
                                    BSP_LCDCTRL_THREEFIVE_PWM,
                                    *brightVal);
    }

    return retVal;
}

static Int32 Bsp_lcdCtrlSelectMode(const Bsp_LcdCtrlHandleObj *pObj,
                                   const UInt32               *mode)
{
    Int32  retVal = FVID2_SOK;
    UInt32 dutyCycle;

    /* Error checking for mode pointer */
    if (BSP_LCD_CTRL_MODE_DE == *mode)
    {
        dutyCycle = 100U;
    }
    else if (BSP_LCD_CTRL_MODE_HSYNC_VSYNC == *mode)
    {
        dutyCycle = 0;
    }
    else
    {
        retVal = FVID2_EBADARGS;
    }

    if (retVal == FVID2_SOK)
    {
        retVal = Bsp_tlc59108SetPin(pObj->createPrms.deviceI2cInstId,
                                    pObj->createPrms.deviceI2cAddr[
                                        BSP_LCDCTRL_TLC59108_INST_0],
                                    BSP_LCDCTRL_THREEFIVE_MODE3,
                                    dutyCycle);
    }

    return retVal;
}

static Int32 Bsp_lcdCtrlGetPanelInfo(const Bsp_LcdCtrlHandleObj *pObj,
                                     Bsp_LcdCtrlPanelInfo       *panelInfo)
{
    Int32 retVal = FVID2_SOK;

    if (NULL == panelInfo)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "NULL argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Detect ATMXT224 first as this is unique. Detecting STM present
         * in 10-inch LCD results in false detect in Tda2xx EVM. */
        retVal = Bsp_deviceI2cProbeDevice(
            pObj->createPrms.deviceI2cInstId,
            (UInt8) LCDCTRL_ATMXT224_TOUCH_I2C_ADDR0);
        if (FVID2_SOK == retVal)
        {
            /* 7-inch 800x480 LCD */
            Fvid2ModeInfo_init(&panelInfo->modeInfo);
            panelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
            panelInfo->modeInfo.width       = 800U;
            panelInfo->modeInfo.height      = 480U;
            panelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
            panelInfo->modeInfo.pixelClock  = 29232U;
            panelInfo->modeInfo.fps         = 60U;
            panelInfo->modeInfo.hBackPorch  = 40U;
            panelInfo->modeInfo.hSyncLen    = 48U;
            panelInfo->modeInfo.hFrontPorch = 40U;
            panelInfo->modeInfo.vBackPorch  = 29U;
            panelInfo->modeInfo.vSyncLen    = 3U;
            panelInfo->modeInfo.vFrontPorch = 13U;

            panelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
            panelInfo->videoDataFormat = FVID2_DF_RGB24_888;
            panelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

            panelInfo->vsPolarity       = FVID2_POL_LOW;
            panelInfo->hsPolarity       = FVID2_POL_LOW;
            panelInfo->actVidPolarity   = FVID2_POL_HIGH;
            panelInfo->fidPolarity      = FVID2_POL_HIGH;
            panelInfo->pixelClkPolarity = FVID2_POL_LOW;
        }
        else
        {
            /* Probe Parallel port to MIPI DSI TC358778 chip @ 0x0E.
             * if found it is OSD 1080P LCD */
            retVal = Bsp_deviceI2cProbeDevice(
                pObj->createPrms.deviceI2cInstId,
                (UInt8) LCDCTRL_TC358778_MIPI_DSI_I2C_ADDR0);
            if (FVID2_SOK == retVal)
            {
                retVal = FVID2_SOK;
                Fvid2ModeInfo_init(&panelInfo->modeInfo);
                panelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
                panelInfo->modeInfo.width       = 1920U;
                panelInfo->modeInfo.height      = 1200U;
                panelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
#if defined (BSP_LCDCTRL_IDK_LCD_32FPS)
                panelInfo->modeInfo.pixelClock  = 78000U;
                panelInfo->modeInfo.fps         = 60U;
                panelInfo->modeInfo.hBackPorch  = 32U;
                panelInfo->modeInfo.hSyncLen    = 16U;
                panelInfo->modeInfo.hFrontPorch = 112U;
                panelInfo->modeInfo.vBackPorch  = 16U;
                panelInfo->modeInfo.vSyncLen    = 2U;
                panelInfo->modeInfo.vFrontPorch = 17U;
#else
                panelInfo->modeInfo.pixelClock  = 147000U;
                panelInfo->modeInfo.fps         = 60U;
                panelInfo->modeInfo.hBackPorch  = 32U;
                panelInfo->modeInfo.hSyncLen    = 16U;
                panelInfo->modeInfo.hFrontPorch = 32U;
                panelInfo->modeInfo.vBackPorch  = 16U;
                panelInfo->modeInfo.vSyncLen    = 2U;
                panelInfo->modeInfo.vFrontPorch = 7U;
#endif
                panelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
                panelInfo->videoDataFormat = FVID2_DF_RGB24_888;
                panelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                panelInfo->vsPolarity       = FVID2_POL_LOW;
                panelInfo->hsPolarity       = FVID2_POL_LOW;
                panelInfo->actVidPolarity   = FVID2_POL_HIGH;
                panelInfo->fidPolarity      = FVID2_POL_HIGH;
                panelInfo->pixelClkPolarity = FVID2_POL_LOW;
            }
            else
            {
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
                retVal = Bsp_deviceI2cProbeDevice(
                             pObj->createPrms.deviceI2cInstId,
                            (UInt8) LCDCTRL_OSD070T1718_LCD_MODULE_I2C_ADDR0);
                if (FVID2_SOK == retVal)
                {
                    /* it is 7-inch 800x480 LCD */
                    retVal = FVID2_SOK;
                    Fvid2ModeInfo_init(&panelInfo->modeInfo);
                    panelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
                    panelInfo->modeInfo.width       = 800U;
                    panelInfo->modeInfo.height      = 480U;
                    panelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
                    panelInfo->modeInfo.pixelClock  = 33000U;
                    panelInfo->modeInfo.fps         = 60U;
                    panelInfo->modeInfo.hBackPorch  = 16U;
                    panelInfo->modeInfo.hSyncLen    = 30U;
                    panelInfo->modeInfo.hFrontPorch = 210U;
                    panelInfo->modeInfo.vBackPorch  = 10U;
                    panelInfo->modeInfo.vSyncLen    = 13U;
                    panelInfo->modeInfo.vFrontPorch = 22U;

                    panelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
                    panelInfo->videoDataFormat = FVID2_DF_RGB24_888;
                    panelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                    panelInfo->vsPolarity       = FVID2_POL_LOW;
                    panelInfo->hsPolarity       = FVID2_POL_LOW;
                    panelInfo->actVidPolarity   = FVID2_POL_HIGH;
                    panelInfo->fidPolarity      = FVID2_POL_HIGH;
                }
                else
                {
#endif
                    /* Probing STM touch @ 0x18U results in I2C bus busy.
                     * Hence default to 10-inch 1280x800 LCD */
                    retVal = FVID2_SOK;
                    Fvid2ModeInfo_init(&panelInfo->modeInfo);
                    panelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
                    panelInfo->modeInfo.width       = 1280U;
                    panelInfo->modeInfo.height      = 800U;
                    panelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
                    panelInfo->modeInfo.pixelClock  = 68900U;
                    panelInfo->modeInfo.fps         = 60U;
                    panelInfo->modeInfo.hBackPorch  = 48U;
                    panelInfo->modeInfo.hSyncLen    = 32U;
                    panelInfo->modeInfo.hFrontPorch = 48U;
                    panelInfo->modeInfo.vBackPorch  = 4U;
                    panelInfo->modeInfo.vSyncLen    = 4U;
                    panelInfo->modeInfo.vFrontPorch = 8U;

                    panelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
                    panelInfo->videoDataFormat = FVID2_DF_RGB24_888;
                    panelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                    panelInfo->vsPolarity       = FVID2_POL_LOW;
                    panelInfo->hsPolarity       = FVID2_POL_LOW;
                    panelInfo->actVidPolarity   = FVID2_POL_HIGH;
                    panelInfo->fidPolarity      = FVID2_POL_HIGH;
                    panelInfo->pixelClkPolarity = FVID2_POL_LOW;
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
                }
#endif
            }
        }
    }

    return (retVal);
}

/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_LcdCtrlHandleObj *Bsp_lcdCtrlAllocObj(void)
{
    UInt32 handleId;
    Bsp_LcdCtrlHandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_lcdCtrlLock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_LCDCTRL_OBJ_STATE_UNUSED ==
            gBspLcdCtrlObj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspLcdCtrlObj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_LCDCTRL_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_LCDCTRL_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_lcdCtrlUnlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_lcdCtrlFreeObj(Bsp_LcdCtrlHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_lcdCtrlLock();

    if (pObj->state != BSP_LCDCTRL_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_LCDCTRL_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);
    }

    /* Release global lock */
    Bsp_lcdCtrlUnlock();

    return (FVID2_SOK);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_lcdCtrlLockObj(Bsp_LcdCtrlHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_lcdCtrlUnlockObj(Bsp_LcdCtrlHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_lcdCtrlLock(void)
{
    BspOsal_semWait(gBspLcdCtrlObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_lcdCtrlUnlock(void)
{
    BspOsal_semPost(gBspLcdCtrlObj.lock);

    return (FVID2_SOK);
}

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
Int32 Bsp_lcdCtrlBackLightCtrlOSD070T1718(UInt32 dutyCycle)
{
#if  !defined(SOC_AM571x)
    UInt16 period, compare = 6650;

    if (100 == dutyCycle)
    {
        period = 6650;
    }
    else
    {
        period = 0;
    }

    /* Start the counter */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBCTL, (UInt16)0xC000);

    /* Update period with presacler division */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_TBPRD, period);

    /* Channel 0 configured with compare A register */
    HW_WR_REG16(SOC_PWMSS2_IEPWM_BASE + PWMSS_EPWM_CMPA, compare);
#endif

    return (BSP_SOK);
}

Int32 Bsp_lcdCtrlBackLightCtrlOSD101T2045(UInt32 dutyCycle)
{
    UInt32 period, compare = 3300;

    if (100 == dutyCycle)
    {
        period = 3200;
    }
    else
    {
        period = 0;
    }

    /* Start the counter */
    ECAPCounterControl(SOC_PWMSS1_IECAP_BASE, ECAP_COUNTER_FREE_RUNNING);

    /* Configure ECAP to generate PWM waveform with 90% duty cycle */
    ECAPAPWMCaptureConfig(SOC_PWMSS1_IECAP_BASE, period, compare);

    return (BSP_SOK);
}
#endif
