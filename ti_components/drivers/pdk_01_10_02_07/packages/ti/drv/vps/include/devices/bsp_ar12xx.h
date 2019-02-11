/*
 *  Copyright (c) Texas Instruments Incorporated 2016-2017
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
 * \ingroup BSP_DRV_DEVICE_API
 * \defgroup BSP_DRV_DEVICE_RADAR_SENSOR_API AR12XX Radar Sensor API
 *
 *  This modules define API specific to AR12XX Radar Sensor.
 *
 * @{
 */

/**
 *  \file bsp_ar12xx.h
 *
 *  \brief AR12XX Radar Sensor API
 */

#ifndef BSP_AR12XX_H_
#define BSP_AR12XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <mmwavelink.h>
#include <rl_sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of cascaded AR12xx supported */
#define BSP_AR12XX_MAX_DEVICES_SUPPORTED (RL_DEVICE_CONNECTED_MAX)

/** \brief Maximum length of the string to identify the radar sensor */
#define BSP_AR12XX_MAX_SENSOR_NAME_LENGTH (32U)

/** \brief Sensor Name for the AR1243 Radar Sensor */
#define BSP_AR12XX_AR1243_NAME "RADAR_SENSOR_AR1243"

/** \brief Enumeration to define which configurations need to written or
 *         over-written by the #Bsp_ar12xxConfigParams API.
 */
typedef enum
{
    BSP_AR12XX_CONFIG_CHANNEL = 0x1U,
    /**< Bit map to re-config/config channel configuration */
    BSP_AR12XX_CONFIG_ADC_OUT = 0x2U,
    /**< Bit map to re-config/config ADC output configuration */
    BSP_AR12XX_CONFIG_DATA_FORMAT = 0x4U,
    /**< Bit map to re-config/config Data format configuration */
    BSP_AR12XX_CONFIG_LOW_POWER_MODE = 0x8U,
    /**< Bit map to re-config/config Low power mode configuration */
    BSP_AR12XX_CONFIG_RF_INIT_CAL_MASK = 0x10U,
    /**< Bit map to configure the RF Calibration */
    BSP_AR12XX_CONFIG_RF_INIT = 0x20U,
    /**< Bit map to perform RF initialization */
    BSP_AR12XX_CONFIG_DATA_PATH = 0x40U,
    /**< Bit map to re-config/config data path configuration */
    BSP_AR12XX_CONFIG_LVDS_CLK = 0x80U,
    /**< Bit map to re-config/config LVDS clock configuration */
    BSP_AR12XX_CONFIG_HSI_CLK = 0x100U,
    /**< Bit map to re-config/config HSI clock configuration */
    BSP_AR12XX_CONFIG_PROFILE_PARAM = 0x200U,
    /**< Bit map to re-config/config profile configuration */
    BSP_AR12XX_CONFIG_CHIRP_PARAM = 0x400U,
    /**< Bit map to re-config/config chirp configuration */
    BSP_AR12XX_CONFIG_BPM_COMMON = 0x800U,
    /**< Bit map to re-config/config BPM common configuration */
    BSP_AR12XX_CONFIG_BPM_CHIRP = 0x1000U,
    /**< Bit map to re-config/config BPM chirp configuration */
    BSP_AR12XX_CONFIG_CSI_LANES = 0x2000U,
    /**< Bit map to re-config/config CSI lane positions and polarity */
    BSP_AR12XX_CONFIG_LDO_BYPASS = 0x4000U,
    /**< Bit map to re-config/config LDO Bypass */
    BSP_AR12XX_CONFIG_FRAME_PARAM = 0x8000U,
    /**< Bit map to re-config/config frame configuration */
    BSP_AR12XX_CONFIG_ALL = 0xFFFFU,
    /**< Bit map to re-config/config all configurations for Frame config. */
    BSP_AR12XX_CONFIG_CONT_STREAMING = 0x10000U
    /**< Bit map to configure and enable continuous streaming. */
}Bsp_Ar12xxConfigOption;

/** \brief Enumeration to define all the input pins to the host device */
typedef enum
{
    BSP_AR12XX_GPIO_INPUT_HOST_INTR = 0U,
    /**< GPIO Host interrupt Pin details */
    BSP_AR12XX_GPIO_INPUT_COUNT = BSP_AR12XX_GPIO_INPUT_HOST_INTR + 1U
                                  /**< Count of the GPIO input pins */
}Bsp_Ar12xxGpioInputPins;

/** \brief Enumeration to define all the output pins from the host device */
typedef enum
{
    BSP_AR12XX_GPIO_OUTPUT_NRESET = 0U,
    /**< GPIO control for nreset output */
    BSP_AR12XX_GPIO_OUTPUT_WARM_RESET,
    /**< GPIO control for warm reset output */
    BSP_AR12XX_GPIO_OUTPUT_NERRORIN,
    /**< GPIO control for Error input pin to the AR12XX */
    BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO,
    /**< SOP mode selection for TDO */
    BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT,
    /**< SOP mode selection for synchronization */
    BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT,
    /**< SOP mode selection for PMIC output */
    BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA,
    /**< UART device Selection GPIO Control */
    BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB,
    /**< UART device Selection GPIO Control */
    BSP_AR12XX_GPIO_OUTPUT_COUNT
    /**< Count of the GPIO output pins */
}Bsp_Ar12xxGpioOutputPins;

/** \brief Enumeration to define AR12xx Frame types */
typedef enum
{
    BSP_AR12XX_FRAME_TYPE_NORMAL = 0U,
    /**< Normal Frame */
    BSP_AR12XX_FRAME_TYPE_ADVANCED = 1U
    /**< Advanced Frame */
}Bsp_Ar12xxFrameType;

/** \brief Enumeration to define AR12xx connection types */
typedef enum
{
    BSP_AR12XX_CONN_TYPE_UNKNOWN = 0U,
    /**< Unknown Connection Type */
    BSP_AR12XX_CONN_TYPE_DIRECT,
    /**< AR12xx Direct Connection */
    BSP_AR12XX_CONN_TYPE_FPDLINK,
    /**< AR12xx Connected via FPD-Link */
    BSP_AR12XX_CONN_TYPE_COUNT
    /**< Count of AR12xx connection types */
}Bsp_AR12xxConnType;
/* @} */
/**
 *  \addtogroup BSP_DRV_DEVICE_API
 *  @{
 */

/**< \brief Test source type for AR12xx */
typedef rlTestSource_t Bsp_Ar12xxTestSource;

/* @} */
/**
 *  \addtogroup BSP_DRV_DEVICE_RADAR_SENSOR_API
 *  @{
 */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief GPIO Input configuration parameters for each radar device
 *         connected to the host SoC.
 */
typedef struct
{
    UInt8  gpioInstId;
    /**< GPIO Instance number being used for the host interrupt.
     *   0 - GPIO1, 1 - GPIO2 and so on. The host interrupt is used by the AR12
     *   to indicate that the AR12 wants to send a message to the host.
     */
    UInt8  gpioPinNum;
    /**< Pin number corresponding to the GPIO host interrupt. 0 - 1st Pin
     *   1 - 2nd Pin and so on.
     */
    UInt16 cpuIntrIdForGpio;
    /**< CPU Interrupt Id used to service the GPIO Interrupt */
} Bsp_Ar12xxGpioInputParams;

/**
 *  \brief GPIO Output configuration parameters for each radar device
 *         connected to the host SoC.
 */
typedef struct
{
    UInt8 gpioInstId;
    /**< GPIO Instance number being used for the host interrupt.
     *   0 - GPIO1, 1 - GPIO2 and so on. The host interrupt is used by the AR12
     *   to indicate that the AR12 wants to send a message to the host.
     */
    UInt8 gpioPinNum;
    /**< Pin number corresponding to the GPIO host interrupt. 0 - 1st Pin
     *   1 - 2nd Pin and so on.
     */
} Bsp_Ar12xxGpioOutputParams;

/**
 *  \brief Device specific parameters used at init call.
 */
typedef struct
{
    char                       radarConfigName[
        BSP_AR12XX_MAX_SENSOR_NAME_LENGTH];
    /**< Name of the radar sensor used by the application */
    UInt32                     mcSpiDevInst;
    /**< McSPI device instance ID used to create the GIO device */
    UInt32                     mcspiChannel;
    /**< McSPI device channel number */
    EDMA3_DRV_Handle           edmaHandle;
    /**< EDMA Handle used to transfer the McSPI data */
    Bsp_Ar12xxGpioInputParams  inGpioParams[BSP_AR12XX_GPIO_INPUT_COUNT];
    /**< GPIO params associated with each AR12 device input to the host */
    Bsp_Ar12xxGpioOutputParams outGpioParams[BSP_AR12XX_GPIO_OUTPUT_COUNT];
    /**< GPIO params associated with each AR12 device output from the host */
    UInt32                     uartDevInst;
    /**< UART Device Instance ID used to flash the AR12xx QSPI Flash */
    UInt32                     i2cDevInst;
    /**< I2C Device Instance ID used for back channel configuration
     *   Applicable for Satellite Radar module via FPD-Link
     */
    UInt32                     i2cDevAddr;
    /**< I2C Device Address used for back channel configuration
     *   Applicable for Satellite Radar module via FPD-Link
     */
    UInt32                     desPortMap;
    /**< Deserializer port number to device ID mapping */
} Bsp_Ar12xxDevInitParams;
/**
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32                     numRadarDevicesInCascade;
    /**< Number of radar devices which are placed in cascade configuration.
     *   The user must populate equivalent number of configuration parameters
     *   corresponding to each radar device in arrays gpioParams.
     */
    UInt32                     sopMode;
    /**< SOP mode that needs to be programmed to the AR12xx. Valid values are
     *   0b101 (SOP mode 5)= Flash programming
     *   0b001 (SOP mode 4) = Functional mode
     *   0b011 (SOP mode 2) = Dev mode
     */
    Int32                      tskPriority;
    /**< Radar driver will create a task for handling communication with the
     *   radar sensor. This input is used to allow the application flexiblity
     *   to appropriately configure the task priority.
     */
    Int32                      masterDevId;
    /**< When multiple devices are connected, one needs to identify which
     *   AR12 is the master which will drive the clock. This number can be
     *   0/1/2/3.
     */
    Bsp_Ar12xxDevInitParams    devParams[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< Device Specific parameters */
} Bsp_Ar12xxInitParams;

/**
 *  \brief Configuration structure for the AR12xx Radar Sensor.
 */
typedef struct
{
    rlChanCfg_t           rfChanCfgArgs;
    /**< Rx/Tx Channel Configuration */
    rlAdcOutCfg_t         adcOutCfgArgs;
    /**< ADC format and payload justification Configuration */
    rlDevDataFmtCfg_t     dataFmtCfgArgs;
    /**< Radar Data format config */
    rlLowPowerModeCfg_t   rfLpModeCfgArgs;
    /**< Low Power mode configuraiton */
    rlChirpCfg_t         *chirpCfgArgs;
    /**< Chirp config API SBC parameters */
    UInt32                numChirpCfgArgs;
    /**< Number of Chirp configuration arguments */
    rlProfileCfg_t       *profileCfgArgs;
    /**< Profile config API SBC parameters */
    UInt32                numProfileCfgArgs;
    /**< Number of profile configuration arguments */
    rlFrameCfg_t         *frameCfgArgs;
    /**< Frame config API SBC parameters */
    rlDevDataPathCfg_t    dataPathCfgArgs;
    /**< Radar Data Path config */
    rlDevDataPathClkCfg_t dataPathClkCfgArgs;
    /**< LVDS clock configuration */
    rlDevHsiClk_t         hsiClkgs;
    /**< Radar High speed clock configuraiton */
    rlDevLaneEnable_t     laneEnCfgArgs;
    /**< Radar Data path lane enable */
    rlRfLdoBypassCfg_t    ldoBypassCfgArgs;
    /**< Radar LDO Bypass configuration argument */
    rlBpmCommonCfg_t      bpmCommnCfgArgs;
    /**< BPM common configration */
    rlBpmChirpCfg_t      *bpmChirpCfgArgs;
    /**< BPM Chirp configration */
    UInt32                numBpmChirpCfgArgs;
    /**< Number of BPM chirp configuration arguments */
    rlDevCsi2Cfg_t        csiConfigArgs;
    /**< Lane configuration of the CSI parameters */
    rlAdvFrameCfg_t       advFrameCfgArgs;
    /**< Advanced Frame config API SBC parameters */
    rlRfInitCalConf_t     calibEnArgs;
    /**< Calibration enable Arguments */
    rlContModeCfg_t       contModeCfgArgs;
    /**< Continuous Mode Transmission arguments */
    uint32_t		  frameType;
    /**< Frame Type. Choices include: #Bsp_Ar12xxFrameType */
} Bsp_Ar12xxConfigObj;

/**
 *  \brief Monitorring call back function. The two params are
 *
 *  \param sbId     Sub Block ID of the monitorring message
 *  \param payload  Payload of the monitorring message. Has the monitorring
 *                  report that the application can see.
 *
 *  \return none
 */
typedef void (*Bsp_Ar12xxMonAppCb) (UInt16 sbId, void * payload);

/**
 *  \brief Monitorring configuration structure for the AR12xx Radar Sensor.
 */
typedef struct
{
    rlMonAnaEnables_t               *monAnaEnable;
    /**< Analog monitoring configuration */
    rlRfCalMonTimeUntConf_t         *monTimeUnitCfg;
    /**< Monitorring time unit */
    rlTempMonConf_t                 *tempMonCfg;
    /**< Temperature sensor monitoring configuration */
    rlRxGainPhaseMonConf_t          *rxGainPhaseMonCfg;
    /**< RX gain and phase monitoring configuration */
    rlRxNoiseMonConf_t              *rxNoiseMonCfg;
    /**< RX noise monitoring configuration */
    rlRxIfStageMonConf_t            *rxIfStageMonCfg;
    /**< RX IF stage monitoring configuration */
    rlAllTxPowMonConf_t             *allTxPowMonCfg;
    /**< TX power monitoring configuration */
    rlAllTxBallBreakMonCfg_t        *allTxBallBreakMonCfg;
    /**< TX ballbreak monitoring configuration */
    rlTxGainPhaseMismatchMonConf_t  *txGainPhaseMismatchMonCfg;
    /**< TX gain and phase mismatch monitoring configuration */
    rlAllTxBpmMonConf_t             *allTxBpmMonCfg;
    /**< TX BPM monitoring configuration */
    rlSynthFreqMonConf_t            *synthFreqMonCfg;
    /**< Synthesizer frequency monitoring configuration */
    rlExtAnaSignalsMonConf_t        *extAnaSigMonCfg;
    /**< External analog signals monitoring configuration */
    rlAllTxIntAnaSignalsMonConf_t   *allTxIntAnaSigMonCfg;
    /**< Internal signals in the TX path monitoring configuration */
    rlRxIntAnaSignalsMonConf_t      *rxIntAnaSigMonCfg;
    /**< Internal Analog signals monitoring configuration */
    rlPmClkLoIntAnaSignalsMonConf_t *pmClkLoIntAnaSigMonCfg;
    /**< Internal signals for PM, CLK and LO monitoring configuration */
    rlGpadcIntAnaSignalsMonConf_t   *gpadcIntAnaSigMonCfg;
    /**< Internal signals for GPADC monitoring configuration */
    rlPllContrVoltMonConf_t         *pllControlVoltMonCfg;
    /**< Internal signals for PLL control voltage monitoring configuration */
    rlDualClkCompMonConf_t          *dualClkCompMonCfg;
    /**< Internal signals for DCC based clock monitoring configuration */
    rlRxSatMonConf_t                *rxSatMonCfg;
    /**< RX saturation monitoring configuration */
    rlSigImgMonConf_t               *sigImgMonCfg;
    /**< Signal and image band energy monitoring configuration */
    rlRfCalMonFreqLimitConf_t       *calMonFreqLimitCfg;
    /**< Radar RF Calibration monitoring Frequency Limit configuration */
    rlRunTimeCalibConf_t            *runTimeCalCfg;
    /**< Radar RF Run time calibration configuration */
    rlCalibrationData_t             *calibDataStoreRestore;
    /**< This should be an array of 3 elements. Calibration data which
     *   application will receive from radarSS and will feed in to the Device
     * in next power up to avoid calibration.
     */
    Bsp_Ar12xxMonAppCb               monReportCallBackFunc;
    /**< Application call back when monitorring async event recieved */
} Bsp_Ar12xxMonConfigObj;


/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/**
 *  \brief AR12XX radar sensor register configuration function.
 *
 *  \param  name        Name of the Radar Sensor confgiuration to be registered.
 *                      One should ensure to provide the same name in initPrms
 *                      of #Bsp_ar12xxInit function.
 *  \param  configObj   Pointer to the radar configuration parameters asctime
 *                      defined by #Bsp_Ar12xxConfigObj.
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxRegisterConfig(
    char name[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH],
    Bsp_Ar12xxConfigObj * configObj);

/**
 *  \brief AR12XX radar sensor driver init function.
 *
 *  Initializes the AR12XX driver.
 *  This function should be called before calling any of sensor APIs and
 *  should be called only once.
 *
 *  \param initPrms     Pointer to the init parameter containing
 *                      instance specific information
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxInit(const Bsp_Ar12xxInitParams *initPrms);

/**
 *  \brief AR12XX radar sensor driver deinit function.
 *
 *  Uninitializes the AR12XX driver and deletes the McSPI driver and should be
 *  called during system shutdown.
 *  Should not be called if Bsp_ar12xxInit() is not called.
 *
 *  \return BSP_SOK on success, else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxDeInit(void);

/**
 *  \brief AR12XX radar sensor boot function.
 *
 *  Switches on the AR12xx sensor and ensures the firmware has finished the
 *  initialization sequence.
 *
 *  \param downloadFirmware  Flag used to indicate whether to load the
 *                           firmware via SPI. If the AR12 flash is
 *                           pre-flashed or programmed via
 *                           #Bsp_ar12xxFlashFirmware, then this flag can be
 *                           0 i.e. Do not load firmware via SPI.
 *                           when 1, the API will try to download the
 *                           firmware via SPI.
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxBoot(UInt32 downloadFirmware);

/**
 *  \brief  Function to configure the different parameters of the radar sensor.
 *
 *  \param  bitMapEnableConfig  Bit map index which defines which parameters
 *                              need to be configured. Refer
 *                              #Bsp_Ar12xxConfigOption to get the bit map.
 *
 *  \return retVal  Returns BSP_SOK if the driver parameters are configured
 *                  correctly. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxConfigParams(UInt32 bitMapEnableConfig);

/**
 *  \brief  Function to configure the different parameters of the radar sensor.
 *
 *  \param  deviceOfInterest Device Index of interest (0/1/2/3)
 *  \param  paramOfInterest  Bit map index which defines which parameter
 *                           need to be read back. Refer
 *                           #Bsp_Ar12xxConfigOption.
 *                           Valid option includes:
 *                           BSP_AR12XX_CONFIG_PROFILE_PARAM
 *                           BSP_AR12XX_CONFIG_CHIRP_PARAM
 *                           BSP_AR12XX_CONFIG_FRAME_PARAM
 *                           Unlike the set param, call this API with only
 *                           one option.
 *  \param  index           For profile config and chirp config this defines
 *                          which index is read. For frame config this field
 *                          is ignored.
 *  \param  ptr             Pointer to the object to which the parameter
 *                          values is returned. The following types of
 *                          parameter pointers should be passed:
 *                          BSP_AR12XX_CONFIG_PROFILE_PARAM - rlProfileCfg_t *
 *                          BSP_AR12XX_CONFIG_CHIRP_PARAM   - rlChirpCfg_t *
 *                          BSP_AR12XX_CONFIG_FRAME_PARAM   - rlFrameCfg_t *
 *
 *  \return retVal  Returns BSP_SOK if the driver parameters are read
 *                  correctly. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxGetConfiguredParam(UInt32 deviceOfInterest,
                                   UInt32 paramOfInterest, UInt32 index,
                                   void *ptr);

/**
 *  \brief  AR12XX radar sensor driver start function. This function will start
 *          the radar sensor operation.
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxStartRadar(void);

/**
 *  \brief  AR12XX radar sensor driver stop function. This function will stop
 *          the radar sensor operation and power it off.
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_ar12xxStopRadar(void);

/**
 *  \brief  Function to get the width and height of the radar frame based on
 *          the configuration for the radar requested. This function should
 *          be called only after #Bsp_ar12xxInit.
 *
 *  \param  deviceId    Device Index for which to get the width & height.
 *  \param  width       Width of the radar frame.
 *  \param  height      Height of the radar frame.
 *
 *  \return retVal      Returns BSP_SOK if the width and height parameters are
 *                      received correctly. BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxGetWidthHeight(UInt32 deviceId, UInt32 *width, UInt32 *height);

/**
 * \brief Function to config monitoring within the AWR sensor
 *
 *  \param  deviceId    Device Index for which to set the monitoring
 *                      configuration. Can be 0/1/2/3...
 * \param sensorMonCfg  Pointer to monitoring configuration Structure.
 *
 * \return retVal       If any monitoring config API fail it return Error code
 *                      without invoking further APIs
 */
Int32 Bsp_ar12xxConfigMonitor(UInt32 deviceId,
                              Bsp_Ar12xxMonConfigObj *sensorMonCfg);

/**
 *  \brief  Function to set some dummy objects that the AR12xx can give to
 *          the host CPU. This enables testing of the algorithm.
 *
 *  \param  deviceId    Device Index for which to set the test source.
 *  \param  testSource  Contains the parameters corresponding to the dummy
 *                      objects.
 *
 *  \return retVal  Returns BSP_SOK if the dummy objects parameters are set
 *                  correctly. BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxEnableDummySource(UInt32 deviceId,
    Bsp_Ar12xxTestSource *testSource);

/**
 *  \brief  Function to erase the flash associated with the AR12xx for storing
 *          the firmware.
 *
 *  \return retVal  Returns BSP_SOK if the AR12xx Flash is successfully erased.
 *                  BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxEraseFirmware(void);

/**
 *  \brief  Function to program the flash associated with the AR12xx with the
 *          firmware which is part of the mmwavedfp package. This API should
 *          always be called after #Bsp_ar12xxEraseFirmware.
 *
 *  \return retVal  Returns BSP_SOK if the AR12xx Flash is successfully flashed.
 *                  BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxFlashFirmware(void);

/**
 *  \brief  Function to unregister a given configuration.
 *
 *  \param  configName  Name of the configuration.
 *
 *  \return retVal      Returns BSP_SOK if the configuration is successfully
 *                      removed. BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxUnRegisterConfig(
    char configName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH]);

/**
 *  \brief  Function to switch to a given configuration. This is an optional
 *          step if the only a single AR1243 configuration is used. If there
 *          are more than one configurations used then one can use the
 *          following API to switch between configurations after
 *          performing #Bsp_ar12xxInit.
 *
 *  \param  deviceId    Device Index for which to switch Configuration.
 *  \param  configName  Name of the configuration.
 *
 *  \return retVal      Returns BSP_SOK if the configuration is
 *                      successfully switched. BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxSwitchConfig(
    UInt32 deviceId,
    char configName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH]);

/**
 *  \brief  Function to get the connection type of AR12.
 *
 *  \return retVal      Returns #Bsp_AR12xxConnType.
 */
Bsp_AR12xxConnType Bsp_ar12xxGetConnType(void);

/**
 *  \brief  Function to read back device temperature.
 *
 *  \param  deviceId        Device ID for which the temperature should be read.
 *                          Can take the values 0/1/2/3
 *  \param  readTempData    This parameter is populated with the temperature
 *                          value read back from the radar sensor.
 *
 *  \return retVal          Returns BSP_SOK if the temperature is read correctly
 */
Int32 Bsp_ar12xxGetTemperature(UInt32 deviceId, rlRfTempData_t * readTempData);

/**
 *  \brief  Function to reconfigure chirps dynamically.
 *
 *  \param  deviceId        Device ID for which the temperature should be read.
 *                          Can take the values 0/1/2/3...
 *  \param  dynChirpData    New chirp configuration data.
 *  \param  numChirpSeg     Number of chirps to configure.
 *
 *  \return retVal          Returns BSP_SOK if the chirps are set correctly.
 */
Int32 Bsp_ar12xxReconfigChirp(UInt32 deviceId,
                              rlDynChirpCfg_t *dynChirpData,
                              UInt32 numChirpSeg);
/**
 *  \brief  Function to reconfigure calibration data.
 *
 *  \param  deviceId        Device ID for which the temperature should be read.
 *                          Can take the values 0/1/2/3...
 *  \param  calibDataStoreRestore    Calibration Data.
 *
 *  \return retVal          Returns BSP_SOK if the calibration is restored
 *                          correctly.
 */
Int32 Bsp_ar12xxRestoreCalibData(UInt32 deviceId,
                                 rlCalibrationData_t* calibDataStoreRestore);

/**
 *  \brief  Function to Start the transmission of the test pattern as specified
 *          in the testPatternCfg.
 *
 *  \param  testPatternCfg  The configuration for the test pattern.
 *
 *  \return retVal          Returns BSP_SOK if test pattern configuration is
 *                          successful.
 */
Int32 Bsp_ar12xxStartTestPattern(rltestPattern_t * testPatternCfg);

/**
 *  \brief Bsp_Ar12xxInitParams structure init function.
 *
 *  \param initPrms     Pointer to #Bsp_Ar12xxInitParams structure.
 *
 */
static inline void Bsp_ar12xxInitParams_init(
    Bsp_Ar12xxInitParams *initPrms);

/**
 *  \brief  Function to set seeds for the test source. This makes the test
 *          source data pattern constant.
 *
 *  \return retVal  Returns BSP_SOK if the seeds are set correctly
 */
Int32 Bsp_ar12xxSetTestSourceSeeds(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Bsp_ar12xxInitParams_init(
    Bsp_Ar12xxInitParams *initPrms)
{
    Bsp_Ar12xxGpioInputParams  inGpioParamsDef =
    {(UInt8) 2, (UInt8) 29, (UInt16) 51};     /* GPIO3, Pin 29, CPU Intr 51 */
    Bsp_Ar12xxGpioOutputParams outGpioParamsDef[BSP_AR12XX_GPIO_OUTPUT_COUNT]
        = {
        /* GPIO3, PIN 19 BSP_AR12XX_GPIO_OUTPUT_NRESET */
        {(UInt8) 2,    (UInt8) 19},
        /* Not Used: BSP_AR12XX_GPIO_OUTPUT_WARM_RESET */
        {(UInt8) 0xFF, (UInt8) 17},
        /* Not Used: BSP_AR12XX_GPIO_OUTPUT_NERRORIN */
        {(UInt8) 0xFF, (UInt8) 5 },
        /* Not Used: BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_TDO */
        {(UInt8) 0xFF, (UInt8) 24},
        /* Not Used:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_SYNCOUT */
        {(UInt8) 0xFF, (UInt8) 25},
        /* Not Used:  BSP_AR12XX_GPIO_OUTPUT_SOP_MODE_SEL_PMICOUT */
        {(UInt8) 0xFF, (UInt8) 26},
        /* Not Used:  BSP_AR12XX_GPIO_OUTPUT_UART_SELECTA */
        {(UInt8) 0x0, (UInt8) 0},
        /* Not Used:  BSP_AR12XX_GPIO_OUTPUT_UART_SELECTB */
        {(UInt8) 0x0, (UInt8) 0}
        };

    if (initPrms != NULL)
    {
        strcpy(initPrms->devParams[0].radarConfigName, BSP_AR12XX_AR1243_NAME);

        /* Can have up to BSP_AR12XX_MAX_DEVICES_SUPPORTED devices in cascade */
        initPrms->numRadarDevicesInCascade = 1U;

        /* McSPI1 is default selection */
        initPrms->devParams[0].mcSpiDevInst = 0U;
        initPrms->devParams[0].mcspiChannel = 0U;

        /* UART1 is default selection */
        initPrms->devParams[0].uartDevInst = 0U;

        /* Should be filled by application */
        initPrms->devParams[0].edmaHandle = NULL;

        memcpy(&initPrms->devParams[0].inGpioParams, &inGpioParamsDef,
               sizeof (inGpioParamsDef));
        memcpy(&initPrms->devParams[0].outGpioParams, outGpioParamsDef,
               sizeof (outGpioParamsDef));
        initPrms->sopMode = 4U;

        /* Radar driver will create a task for handling communication with the
         * radar sensor. This input is used to allow the application flexiblity
         * to appropriately configure the task priority.
         */
        initPrms->tskPriority = 1U;

        initPrms->masterDevId = 0U;
    }

    return;
}

#ifdef __cplusplus
}
#endif  /* #ifndef BSP_AR12XX_H_ */

#endif

/* @} */
