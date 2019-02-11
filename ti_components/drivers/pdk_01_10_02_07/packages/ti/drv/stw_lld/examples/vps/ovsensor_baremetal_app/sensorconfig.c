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
#include <stdint.h>
#include <stdio.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ov_sensorconfig.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>
#include <ti/csl/hw_types.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#endif
#include <ti/csl/csl_gpio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#ifndef TI814X_BUILD
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#endif

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/

/* OV sensor decvice address*/
#define OV10630_ADDR                  (0x30)
#define BOARD_IO_EXP_I2C_ADDR_2       (0x26)

#ifdef BUILD_A8
#define I2C2_INT_NUM                  (30U)

#elif  (defined (BUILD_M3VPSS)) || (defined (__TI_ARM_V7M4__))
#define I2C2_INT_NUM                  (41U)
#define I2C5_INT_NUM                  (60U)

#elif defined (_TMS320C6X)
#define I2C2_INT_NUM                  (89U)

#elif defined (__ARM_ARCH_7A__)
#define I2C2_INT_NUM                  (57U)
#if defined (SOC_TDA2EX)
#define I2C5_INT_NUM                  (60U)
#endif
#endif

#if (defined (__TI_ARM_V7M4__))
#define POLLED_MODE 1
#define INTERRUPT_MODE 0
#else
#define POLLED_MODE 0
#define INTERRUPT_MODE 1
#endif

#if INTERRUPT_MODE
#if defined (SOC_TDA2EX)
#define MPU_XBAR_INSTANCE             (55U)
#else
#define MPU_XBAR_INSTANCE             (52U)
#endif
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA3XX)
#define HSI2C_INST HSI2C_INST_1
#elif defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
#define HSI2C_INST HSI2C_INST_4
#else
#define HSI2C_INST HSI2C_INST_2
#endif

#define XBAR_INT_LINE                 (4U)
#define XBAR_NUM                      (18U)

#define REG32(x)                        *((volatile unsigned int *) (x))
/*Todo : codecleanup to use starterware PAD MUX config instead of setPinmuxRegs
**/
#define PULLTYPESELECT_DOWN             (0x00U)
#define INPUTENABLE_OUT                 (0x00U)
#define DEFAULT                         (0xFF)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             (SOC_GPIO4_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            (13U)
#define BOARD_GPIO_PIN_MUX1_SEL1            (14U)
#define BOARD_GPIO_PIN_MUX2_SEL0            (15U)
#define BOARD_GPIO_PIN_MUX2_SEL1            (16U)
#define BOARD_GPIO_BASE_POWER_DWN           (SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              (17U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((UInt32) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((UInt32) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((UInt32) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((UInt32) 7U)

#define BOARD_PCF8575_VIN2_S0               (0x04U)
#if defined (SOC_TDA2EX)
#define BOARD_PCF8575_VIN2_S2               (0x40U)
#else
#define BOARD_PCF8575_CAM_FPD_MUX_S0        (0x08U)
#endif

/**
 *  \name External Video Device ID.
 */

/** \brief OV10630 video sensor driver ID. */
#define VID_SENSOR_OV10630    0x0

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
LLD_hsi2cErrorCode_t txStatus;

volatile uint32_t    intStatus = 1;
int32_t gTestStatus = STW_SOK;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/

uint32_t ovSensorConfig(hsI2cHandle i2cHandle);
Int32 Board_Tda2xxGPIOConfigure(hsI2cHandle i2cHandle, Int32 sensorDevID);
Int32 Board_Tda2xxInit(void);

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);
Int32 Platform_Tda3xxInit();

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static Int32 setPinmuxRegs(UInt32 mode_index, UInt32 offset, UInt32 pupd_info)
{
    Int32 muxVal;

    if (offset != 0xffff)
    {
        muxVal =
            HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        muxVal &= ~(0x0FU);
        muxVal |= (mode_index & 0x0000000FU);

        if (pupd_info != DEFAULT)
        {
            muxVal &= ~(0x70000U);
            muxVal |= ((pupd_info & 0x07U) << 16U);
        }
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    return 0;
}

#endif

#if defined (SOC_TDA3XX)
void sensorConfigAppInit(void)
{
    Int32 retVal;
    stwAppInitParams_t stwAppInitParams;

    /* System init */
    StwUtils_appInitParams_init(&stwAppInitParams);
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        printf("\r\nSystem Init Failed ");
        gTestStatus = STW_EFAIL;
    }
}

void sensorConfigBoardMuxConfig(void)
{
    Int32 retVal;

    BOARDSelectDevice(DEVICE_ID_OV1063X, 0);

    retVal = BOARDSelectMode(DEVICE_ID_OV1063X, 0, BOARD_MODE_VIDEO_8BIT);
    if (retVal != STW_SOK)
    {
        printf("\r\n Board Select Mode Failed ");
        gTestStatus = STW_EFAIL;
    }
}

Int32 Platform_Tda3xxInit()
{
    Int32 retVal = STW_SOK;

    /* Unlock MMR_LOCK_2 For XBAR settings */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xF757FDC0U;

    /* XBAR VIP1_IRQ1 to IPU1_27 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_27, VIP1_IRQ);

    /* XBAR DISPC_IRQ to IPU1_23 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_23, DISPC_IRQ);
    /* Lock MMR_LOCK_2 */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xFDF45530U;

    return retVal;
}

#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
Int32 Platform_Tda2xxInit()
{
    int32_t retVal = 0;

    /* GPIO mux, OV_PWDN of vision board is connected to GPIO6_17
     * PAD=xref_clk0, PIN=gpio6_17 */
    setPinmuxRegs(14, CTRL_CORE_PAD_XREF_CLK0, DEFAULT);

    /* GPIO PIN MUX settings
     * PAD=vin2a_d12,PIN=gpio4_13
     * PAD=vin2a_d13,PIN=gpio4_14
     * PAD=vin2a_d14,PIN=gpio4_15
     * PAD=vin2a_d15,PIN=gpio4_16
     */
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D12,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D13,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D14,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D15,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));

    /* PAD=mcasp2_axr6, PIN=gpio2_29
     * PAD=mcasp2_axr4, PIN=gpio1_4
     * PAD=mcasp2_axr5, PIN=gpio6_7 */
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));

    /* I2C mux */
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C1_SDA, DEFAULT);
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C1_SCL, DEFAULT);
#if defined (SOC_TDA2EX) || defined (SOC_TDA2PX)
    /* I2C5 mux */
    setPinmuxRegs(10, CTRL_CORE_PAD_MCASP1_AXR0, DEFAULT);
    setPinmuxRegs(10, CTRL_CORE_PAD_MCASP1_AXR1, DEFAULT);
#else
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C2_SDA, DEFAULT);
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C2_SCL, DEFAULT);
#endif

    /*
     * Cross bar setup
     */
    /* Unlock MMR_LOCK_2  */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xF757FDC0;
    /* XBAR VIP1_IRQ1 to IPU1_27
     * XBAR VIP2_IRQ1 to IPU1_28 */
    *((volatile UInt32 *) 0x4A0027E8U) =
        ((UInt32) 352 << 16) | (UInt32) 351;
    /* XBAR VIP3_IRQ1 to IPU1_29
     * XBAR VPE1_IRQ1 to IPU1_30 */
    *((volatile UInt32 *) 0x4A0027ECU) =
        ((UInt32) 354 << 16) | (UInt32) 353;
    /* XBAR DISPC_IRQ at IPU1_23 */
    *((volatile UInt32 *) 0x4A0027E0U) = (UInt32) 20;
    /* XBAR HDMI_IRQ at IPU1_26 */
    *((volatile UInt32 *) 0x4A0027E4U) = ((UInt32) 96 << 16);
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C2_IRQ to IPU1_42 */
    *((volatile UInt32 *) 0x4A002804U) =
        ((UInt32) 52 << 16) | (UInt32) 51;
    *((volatile UInt32 *) 0x4A002B94U) =
        ((UInt32) 132 << 16) | (UInt32) 133;

    return retVal;
}

#endif

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
    volatile uint8_t      done = 1U;

#if (INTERRUPT_MODE)

#ifdef BUILD_M3VPSS
    PlatformXBARIntMux(XBAR_INT_LINE, XBAR_NUM);
#endif

    Intc_Init();
    Intc_IntEnable(0);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    Platform_Tda2xxInit();
    Board_Tda2xxInit();
    PlatformUART1SetPinMux();

#ifdef __ARM_ARCH_7A__

    PlatformUnlockMMR();

#if INTERRUPT_MODE
#if defined (SOC_TDA2EX)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   MPU_XBAR_INSTANCE,
                   I2C5_IRQ);
#else
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   MPU_XBAR_INSTANCE,
                   I2C2_IRQ);
#endif
#endif
#endif
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
    UART_Init(UART1_INST);
#endif

#if defined (SOC_TDA3XX)
    Platform_Tda3xxInit();
    sensorConfigAppInit();
#endif

    UARTprintf("\r\nSensor Config Test Application");

#if defined (TI814X_BUILD)
    /*
     * Pad configuration has to be done in priviledge mode
     * or from gel file while running from a8
     */
    PlatformI2CSetPinMux();
    PlatformI2CClockEnable();
#endif
#ifdef __TI_ARM_V7M4__
#if defined (SOC_TDA2PX)
    initPar.i2cIntNum = I2C5_INT_NUM;
#else
    initPar.i2cIntNum = I2C2_INT_NUM;
#endif
#else
#if defined (SOC_TDA2EX)
    initPar.i2cIntNum = I2C5_INT_NUM;
#else
    initPar.i2cIntNum = I2C2_INT_NUM;
#endif
#endif
    initPar.i2cBusFreq = I2C_NORMAL;

#if INTERRUPT_MODE
    initPar.opMode = HSI2C_OPMODE_INTERRUPT;
#endif

#if POLLED_MODE
    initPar.opMode = HSI2C_OPMODE_POLLED;
#endif
    initPar.i2cOwnAddr   = 0;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST, (lldHsi2cAppCallback) i2c_callback,
                             NULL);

    Intc_IntRegister(initPar.i2cIntNum, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(initPar.i2cIntNum, 1, 0);
    Intc_SystemEnable(initPar.i2cIntNum);

    ovSensorConfig(i2cHandle);

    lld_i2c_close(&i2cHandle);

    lld_i2c_deinit(HSI2C_INST);

    if (gTestStatus == STW_SOK)
    {
#ifndef TI814X_BUILD
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
#endif
        UARTprintf("\r\nSensor Config Test Pass");
    }
    else
    {
#ifndef TI814X_BUILD
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
#endif
        UARTprintf("\r\nSensor Config Test Fail");
    }

    while (done) ;

    return 0;
}

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData)
{
    intStatus = 0;

    txStatus = status;

    if (LLD_HSI2C_SUCCESS == status)
    {
        /* printf("\r\n Error in sensor config");*/
    }
    else
    {
        /*printf("\r\nSensor config done");*/
    }
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

uint32_t ovSensorConfig(hsI2cHandle i2cHandle)
{
    uint32_t                   retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count;
    uint32_t                   sensorScriptSize;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint16_t                   regAddr, regReadValHighBits, regReadValLowBits;
    uint8_t data[4];

#if defined (SOC_TDA2XX)|| defined (SOC_TDA2EX)
    Board_Tda2xxGPIOConfigure(i2cHandle, VID_SENSOR_OV10630);
#elif defined (SOC_TDA3XX)
    sensorConfigBoardMuxConfig();
#endif

    i2cXferParams.bufLen = 3;
    i2cXferParams.buffer = &data[0];
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = (uint8_t) OV10630_ADDR;
    i2cXferParams.timeout   = 4000;

    data[0] = 0x30;
    data[1] = 0x03;
    data[2] = 0x20;
    retVal  = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\r\nOV Reg writes failed");
        gTestStatus = STW_EFAIL;
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nOV Reg writes failed");
        gTestStatus = STW_EFAIL;
    }
#endif

    regAddr = 0x3003;
    data[0] = (uint8_t) (regAddr >> 8);
    data[1] = (uint8_t) (regAddr);
    i2cXferParams.bufLen = 2;
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START /*
                                                                                *|
                                                                                *LLD_HSI2C_STOP*/;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\r\nOV Reg writes failed");
        gTestStatus = STW_EFAIL;
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nOV Reg writes failed");
        gTestStatus = STW_EFAIL;
    }
#endif

    sampleDelay(1000);

    i2cXferParams.bufLen = 2;
    i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\r\nOV Reg read failed\r\n");
        gTestStatus = STW_EFAIL;
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\r\nOV Reg read failed\r\n");
        gTestStatus = STW_EFAIL;
    }
#endif

    regReadValHighBits = data[0];
    regReadValLowBits  = data[1];
    UARTprintf("\r\nRegister %d value = %d", regAddr,
               (((regReadValHighBits <<
                  8) & 0xFF00) | (regReadValLowBits & 0xFF)));

    sensorScriptSize = sizeof (SensorConfigScript_OV) / (3 * sizeof (uint32_t));

    i2cXferParams.bufLen = 3;
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP;
    for (count = 0; count < sensorScriptSize; count++)
    {
        data[0] = (SensorConfigScript_OV[count][0] & 0xffff) >> 8;  /* MSB*/

        data[1] = (SensorConfigScript_OV[count][0] & 0xff);         /* LSB*/

        data[2] = (SensorConfigScript_OV[count][1] & 0xff);         /* value*/

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        sampleDelay(1000);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\r\nOV Reg writes failed");
            gTestStatus = STW_EFAIL;
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\r\nOV Reg writes failed");
            gTestStatus = STW_EFAIL;
        }
#endif
    }

    return retVal;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
Int32 Board_Tda2xxGPIOConfigure(hsI2cHandle i2cHandle, Int32 sensorDevID)
{
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t data[4], retVal;

    if (sensorDevID == VID_SENSOR_OV10630)
    {
        /*
         * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
         */

        GPIOPinWrite(
            BOARD_GPIO_BASE_POWER_DWN,
            BOARD_GPIO_PIN_OV_PWDN,
            GPIO_PIN_LOW);

        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];
        i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP |
                               LLD_HSI2C_IGNORE_BUS_BUSY;
        i2cXferParams.slaveAddr = (uint8_t) BOARD_IO_EXP_I2C_ADDR_2;
        i2cXferParams.timeout   = 4000;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\r\nReg Read failed");
            gTestStatus = STW_EFAIL;
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\r\nReg Read failed");
            gTestStatus = STW_EFAIL;
        }
#endif
        /* Configure board mux */
        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];
        i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP;
        i2cXferParams.slaveAddr = (uint8_t) BOARD_IO_EXP_I2C_ADDR_2;
        i2cXferParams.timeout   = 4000;

#if defined (SOC_TDA2EX)
        data[0] |= (BOARD_PCF8575_VIN2_S2);
#else
        data[0] |= (BOARD_PCF8575_CAM_FPD_MUX_S0);
#endif
        data[0] &= ~((UInt8) (BOARD_PCF8575_VIN2_S0));;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\r\nMux writes failed");
            gTestStatus = STW_EFAIL;
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\r\nMux writes failed");
            gTestStatus = STW_EFAIL;
        }
#endif
        /* By default set to 8-bit mode for all ports by setting
         * Demux_FPD_A,B,C to (1,0,1)  for OV*/
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_A,
            BOARD_GPIO_PIN_DEMUX_FPD_A,
            GPIO_PIN_HIGH);
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_B,
            BOARD_GPIO_PIN_DEMUX_FPD_B,
            GPIO_PIN_LOW);
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_C,
            BOARD_GPIO_PIN_DEMUX_FPD_C,
            GPIO_PIN_HIGH);

        /*
         * Select CPLD mux to select between sensors/decoder in vision
         * daughter card
         *
         * MUX Signal mapping
         * ------------------
         * MUX1_SEL0 - GPIO4_13 (Mux mode 15, muxed with VIN2A_D12)
         * MUX1_SEL1 - GPIO4_14 (Mux mode 15, muxed with VIN2A_D13)
         * MUX2_SEL0 - GPIO4_15 (Mux mode 15, muxed with VIN2A_D14)
         * MUX2_SEL1 - GPIO4_16 (Mux mode 15, muxed with VIN2A_D15)
         *
         *                  MUX1_SEL0     MUX1_SEL1   MUX2_SEL0   MUX2_SEL1
         *                  -----------------------------------------------
         * OV Imager            1             0           1           0
         *
         */

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX1_SEL0,
            GPIO_PIN_HIGH);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX1_SEL1,
            GPIO_PIN_LOW);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX2_SEL0,
            GPIO_PIN_HIGH);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX2_SEL1,
            GPIO_PIN_LOW);
    }

    return 0;
}

Int32 Board_Tda2xxInit(void)
{
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_MUX_SEL);
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_A);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_B);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_C);

    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_A,
        BOARD_GPIO_PIN_DEMUX_FPD_A,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_B,
        BOARD_GPIO_PIN_DEMUX_FPD_B,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_C,
        BOARD_GPIO_PIN_DEMUX_FPD_C,
        GPIO_DIR_OUTPUT);
    return 0;
}

#endif
