/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/soc.h>
#include <ov_sensorconfig.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/vps/include/common/trace.h>

#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/i2clld/src/lld_hsi2c_edma.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

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

static void videoLoopbackAppInit(void);
static int32_t videoLoopbackModuleInit(void);
static void sensor_config(void);

static uint32_t ovSensorConfig(uint32_t ovSensorI2cInstId, uint32_t ovSensorI2cAddr);
#if defined (SOC_TDA2PX)
#else
static UInt32 LCDConfig(uint32_t lcdCtrlI2cInstId, uint32_t lcdCtrlI2cAddr);
#endif
static void LCDConfigMain(void);
void sampleDelay(uint32_t delay);
static void videoLoopbackCaptInit(uint32_t ovSensorInstId);
static void videoLoopbackDSSInit(uint32_t lcdCtrlInstId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Int32 gTestStatus;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void App_boardInit(void)
{
    /* Workaround: Wait for SBL running on host proc to complete. Otherwise
     * SBL and this app will write to UART, corrupting the console output */
    StwUtils_appWaitForSbl();

    /*** START POINT ***/
    videoLoopbackAppInit();

    UARTPuts("\r\nVideoLoopback Test Application", -1);

    videoLoopbackModuleInit();

    /* Sensor configuation */
    sensor_config();

    /* Configure LCD */
    LCDConfigMain();

    return;
}

void App_logResult(Int32 status)
{
    if (status == STW_SOK)
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
        UARTPuts("\r\nVideoLoopback Test Pass", -1);
    }
    else
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTPuts("\r\nVideoLoopback Test Fail", -1);
    }

    return;
}

static void videoLoopbackAppInit(void)
{
    Int32 retVal;
    stwAppInitParams_t stwAppInitParams;

    /* System init */
    Intc_Init();
    Intc_IntEnable(0);

    StwUtils_appInitParams_init(&stwAppInitParams);
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        printf("\r\nSystem Init Failed ");
        gTestStatus = STW_EFAIL;
    }
}

static int32_t videoLoopbackModuleInit(void)
{
    int32_t retVal = STW_SOK;
    uint32_t drvInstId = DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0;
#if defined (SOC_TDA2EX)
    if (CSL_getSocSiliconPackageType() == CSL_SOC_SILICON_PACKAGE_TYPE_17X17)
    {
        drvInstId = DEVICE_MODULE_DSS_DISPC_OVLY_DPI3_INST_ID_1;
    }
#endif

    /* PinMux Configuration for VOUT1 */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_DCTRL,
                            drvInstId,
                            BOARD_MODE_DEFAULT);

#if defined (SOC_TDA2EX)
    /* Set the VIN mux at control module level */
    HW_WR_FIELD32(
        (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
         CTRL_CORE_VIP_MUX_SELECT),
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A,
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A);

    /* PinMux Configuration for VIN2A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);

#else
    /* PinMux Configuration for VIN1A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);
#endif
    return retVal;
}

static int32_t lcdBoardInfoGet(uint32_t *lcdCtrlInstId,
                               uint32_t *lcdCtrlI2cInstId,
                               uint32_t *lcdCtrlI2cAddr)
{
    int32_t status = STW_SOK;
    uint32_t drvInstId = DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0;
#if defined (SOC_TDA2EX)
    if (PlatformGetSiliconPackageType() == PLATFORM_SILICON_PACKAGE_TYPE_17X17)
    {
        drvInstId = DEVICE_MODULE_DSS_DISPC_OVLY_DPI3_INST_ID_1;
    }
#endif

    *lcdCtrlInstId = BOARDGetVideoDeviceInstId(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        drvInstId);

    *lcdCtrlI2cInstId = BOARDGetVideoDeviceI2cInstId(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        drvInstId);

    *lcdCtrlI2cAddr = BOARDGetVideoDeviceI2cAddr(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        drvInstId);

    return status;
}

static int32_t ovSensorBoardInfoGet(uint32_t *ovSensorInstId,
                                    uint32_t *ovSensorI2cInstId,
                                    uint32_t *ovSensorI2cAddr)
{
    int32_t  status = STW_SOK;
    uint32_t vipModInstNum;

#if defined (SOC_TDA2EX)
    vipModInstNum = DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0;
#else
    vipModInstNum = DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0;
#endif

    *ovSensorInstId = BOARDGetVideoDeviceInstId(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    *ovSensorI2cInstId = BOARDGetVideoDeviceI2cInstId(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    *ovSensorI2cAddr = BOARDGetVideoDeviceI2cAddr(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    return status;
}

static void sensor_config(void)
{
    uint32_t ovSensorInstId, ovSensorI2cInstId, ovSensorI2cAddr;
    int32_t  retVal;

    retVal = ovSensorBoardInfoGet(&ovSensorInstId,
                                  &ovSensorI2cInstId, &ovSensorI2cAddr);
    if (retVal != STW_SOK)
    {
        UARTprintf("\r\nOV Sensor Board Get Info Failed ");
        gTestStatus = STW_EFAIL;
    }

    videoLoopbackCaptInit(ovSensorInstId);

    ovSensorConfig(ovSensorI2cInstId, ovSensorI2cAddr);

    UARTprintf("\r\nSensor config done ");
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

static uint32_t ovSensorConfig(uint32_t ovSensorI2cInstId, uint32_t ovSensorI2cAddr)
{
    uint32_t          retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t count, k;
    uint32_t          sensorScriptSize;
    uint16_t          regAddr;
    uint8_t           data[4];

    data[0] = 0x30;
    data[1] = 0x03;
    data[2] = 0x20;

    retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                ovSensorI2cAddr,
                                &data[0],
                                3);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nI2c write failed ");
        gTestStatus = STW_EFAIL;
    }

    regAddr = 0x3003;
    data[0] = (uint8_t) (regAddr >> 8);
    data[1] = (uint8_t) (regAddr);

    retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                ovSensorI2cAddr,
                                &data[0],
                                2);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nI2c write failed ");
        gTestStatus = STW_EFAIL;
    }

    retVal = DEVICEI2cRawRead8(ovSensorI2cInstId,
                               ovSensorI2cAddr,
                               &data[0],
                               2);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nI2c Read failed ");
        gTestStatus = STW_EFAIL;
    }

    sensorScriptSize = sizeof (SensorConfigScript_OV) / (3 * sizeof (uint32_t));

    for (count = 0; count < sensorScriptSize; count++)
    {
        data[0] = (SensorConfigScript_OV[count][0] & 0xffff) >> 8;  /* MSB */

        data[1] = (SensorConfigScript_OV[count][0] & 0xff);         /* LSB  */

        data[2] = (SensorConfigScript_OV[count][1] & 0xff);         /* value  */

        retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                    ovSensorI2cAddr,
                                    &data[0],
                                    3);

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\r\nI2c write failed ");
            gTestStatus = STW_EFAIL;
        }
    }

    return retVal;
}

static void LCDConfigMain(void)
{
    uint32_t lcdCtrlInstId, lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    int32_t  retVal;

    printf("LCD Config\r\n");

    retVal = lcdBoardInfoGet(&lcdCtrlInstId,
                             &lcdCtrlI2cInstId, &lcdCtrlI2cAddr);
    if (retVal != STW_SOK)
    {
        UARTprintf("\r\nLCD Board Get Info Failed ");
        gTestStatus = STW_EFAIL;
    }

    videoLoopbackDSSInit(lcdCtrlInstId);
#if defined (SOC_TDA2PX)
#else
    LCDConfig(lcdCtrlI2cInstId, lcdCtrlI2cAddr);
#endif

    printf("LCD config done\r\n");
}

#if defined (SOC_TDA2PX)
#else
static UInt32 LCDConfig(uint32_t lcdCtrlI2cInstId, uint32_t lcdCtrlI2cAddr)
{
    UInt32 retVal = LLD_HSI2C_SUCCESS;
    UInt8  data[2];

/* For Tda3xx board its done in videoLoopbackAppinit API */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)

    /* Configure board mux */
    data[0] = 0xDBU;
    data[1] = 0xDBU;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    /* Delay is required to stabalize TLC after it is poered on */
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("I2c failed: Step 1\r\n");
        gTestStatus = STW_EFAIL;
    }
#endif
    data[0] = 0x00U;
    data[1] = 0x01U;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("I2c failed: Step 2\r\n");
        gTestStatus = STW_EFAIL;
    }

    data[0] = 0x0CU;
    data[1] = 0x21U;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("I2c failed: Step 3\r\n");
        gTestStatus = STW_EFAIL;
    }

    data[0] = 0x04U;
    data[1] = 0xFFU;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("I2c failed: Step 4\r\n");
        gTestStatus = STW_EFAIL;
    }

    data[0] = 0x0DU;
#if defined (SOC_TDA3XX) || defined (SOC_TDA2EX)
    /* For LG LCD panel, the bit 8 of TLC specified the pixel polarity at
     * which data should be sampled - configuring it to rising edge as there
     * is a inverter in LCD.
     */
    data[1] = 0x51U;
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    data[1] = 0x01U;
#endif
    retVal = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                lcdCtrlI2cAddr,
                                &data[0],
                                2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("I2c failed: Step 5\r\n");
        gTestStatus = STW_EFAIL;
    }
    return retVal;
}
#endif

static void videoLoopbackCaptInit(uint32_t ovSensorInstId)
{
    Int32 retVal;

    retVal = BOARDPowerOnDevice(DEVICE_ID_OV1063X, ovSensorInstId, TRUE);
    if (retVal != STW_SOK)
    {
        printf("\r\nBoard Power On OV Sensor Device Failed ");
        gTestStatus = STW_EFAIL;
    }

    BOARDSelectDevice(DEVICE_ID_OV1063X, ovSensorInstId);

    retVal = BOARDSelectMode(DEVICE_ID_OV1063X,
                             ovSensorInstId, BOARD_MODE_VIDEO_8BIT);
    if (retVal != STW_SOK)
    {
        printf("\r\n Board Select Mode Failed ");
        gTestStatus = STW_EFAIL;
    }
}

static void videoLoopbackDSSInit(uint32_t lcdCtrlInstId)
{
    Int32 retVal;

    retVal = BOARDPowerOnDevice(DEVICE_ID_LCD, lcdCtrlInstId, TRUE);
    if (retVal != STW_SOK)
    {
        printf("\r\nBoard Power On LCD Device Failed ");
        gTestStatus = STW_EFAIL;
    }

    BOARDSelectDevice(DEVICE_ID_LCD, lcdCtrlInstId);

    retVal = BOARDSelectMode(DEVICE_ID_LCD, lcdCtrlInstId,
                             BOARD_MODE_VIDEO_24BIT);
    if (retVal != STW_SOK)
    {
        printf("\r\n Board Select Mode Failed ");
        gTestStatus = STW_EFAIL;
    }
}

