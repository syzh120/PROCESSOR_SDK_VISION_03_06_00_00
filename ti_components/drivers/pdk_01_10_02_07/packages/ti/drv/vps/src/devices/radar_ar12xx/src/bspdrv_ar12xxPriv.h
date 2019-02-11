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
 *  \file bspdrv_ar12xxPriv.h
 *
 *  \brief AR12XX Radar sensor internal header file.
 */

#ifndef BSP_AR12XX_PRIV_H_
#define BSP_AR12XX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <ti/sysbios/io/GIO.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_utilsQue.h>

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>

#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <mmwavelink.h>
#include <rl_sensor.h>

#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>

#include <ti/drv/vps/src/devices/radar_ar12xx/src/bspdrv_ar12xxCrc.h>
#include <ti/drv/vps/src/devices/radar_ar12xx/src/bspdrv_ar12xxInternal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Maximum time out for any operation to finish */
#define BSP_AR12XX_TIMEOUT_MAX (0xFFFFFFFFU)

/** \brief Maximum number of radar configuration sets supported */
#define BSP_AR12XX_MAX_CONFIG_SUPPORTED (5U)

/** Num of McSPI instances supported by the device driver */
#if defined (CSL_NUM_MCSPI_INST)
#define BSP_AR12XX_NUM_MCSPI_INST        (CSL_NUM_MCSPI_INST)
#else
#define BSP_AR12XX_NUM_MCSPI_INST        (1U)
#endif

/** Num of async messages supported by the device driver */
#define BSP_AR12XX_MAX_ASYNC_MESSAGES_SUPPORTED (32U)

/** Maximum number of instances of UART supported by TDA3xx */
#define BSP_AR12XX_NUM_UART_INST (3U)

/** \brief Type definition for the the call back function that should be
 *          called from a different task context.
 */
typedef void (*BspDrv_ar12xxSpawnCallBack)(const void *pValue);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Container structure to store the AR12XX sensor names
 *         and configuration parameters.
 */
typedef struct Bsp_ar12xxSensorObj_t
{
    UInt32               isUsed;
    /**< Flag to indicate if the sensor location is already in use */
    char                 radarConfigName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH];
    /**< Radar sensor name to identify the radar sensor */
    Bsp_Ar12xxConfigObj *sensorConfigObj;
    /**< Configuration object for the radar sensor */
} Bsp_ar12xxSensorObj;

/**
 *  \brief AR12XX communication handle object which contains the required
 *         information for communication with the AR12 devices.
 */
typedef struct
{
    UInt32           deviceIdx;
    /**< Device Index of the corresponding AR12x instance */
    GIO_Handle       mcspiHandle;
    /**< GIO Handle for McSPI */
    GIO_Params       mcspiIoPrms;
    /**< McSPI GIO parameters used while creating the driver */
    Mcspi_ChanParams mcspiChanParams;
    /**< McSPI Channel parameters */
    UInt32           backChI2cInstId;
    /**< Satellite Radar Back Channel I2C instance ID */
    UInt32           backChI2cAddr;
    /**< Satellite Radar Back Channel I2C device address */
} Bsp_ar12xxDeviceCommObj;

/**
 *  \brief Pointer to the radar McSPI communication object.
 */
typedef Bsp_ar12xxDeviceCommObj *Bsp_ar12xxRadarCommHandle;

/**
 *  \brief AR12XX global driver object.
 */
typedef struct Bsp_ar12xxObj_t
{
    Bsp_Ar12xxInitParams       initPrmsCopy;
    /**< Copy of the init parameters */
    UInt32                     radarConfigId[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< Index of the radar sensor in #gBspAr12xxSensorCfgList */
    UInt32                     devIdxMap;
    /**< One hot encoding of the devices present in the host integration */
    Mcspi_Params               mcspiCfgPrms;
    /**< McSPI parameters to be configured during initialization */
    Bsp_ar12xxDeviceCommObj    radarDevCommObj[BSP_AR12XX_MAX_DEVICES_SUPPORTED
    ];
    /**< Radar Communication objects to hold the McSPI device specific
     *   configuration parameters.
     */
    RL_P_EVENT_HANDLER         radarGpioIntrHandler;
    /**< Interrupt Handler for the GPIO interrupt */
    UInt32                     radarInitCompleteFlag;
    /**< Flag to indicate that the initialization has completed */
    UInt32                     radarDevStartCompleteFlag;
    /**< Flag to indicate that the radar device start has completed */
    UInt32                     radarRfInitComplete;
    /**< Flag to indicate that the radar RF initialization is complete */
    UInt32                     mmwl_bSensorStarted;
    /**< Flag to indicate that the radar RF calibration is complete */
    UInt32                     mmwl_runTimeCalibDone;
    /**< Flag to indicate that the Runtime Calibration is complete */
    UInt32                     maxSleepTime;
    /**< This parameter is calculated to find the max time to sleep before
     *   issuing Dynamic frame config.
     */
    BspUtils_QueHandle         gpioAsyncEvtQueHandle;
    /**< Handle for the queue used to store the device Ids from which async
     *   events are generated.
     */
    UInt32                     asyncEvtDevQue[BSP_AR12XX_MAX_ASYNC_MESSAGES_SUPPORTED];
    /**< Queue which holds the device Ids for all the devices which have
     *   sent a host interrupt.
     */
    BspOsal_TaskHandle         radarDevTskHndl;
    /**< Task Handle used to run radar communication */
    BspDrv_ar12xxSpawnCallBack appSpawnCb;
    /**< This function needs to be used to post a semaphore. Application must
     *   must create a Task which will execute a function passed from the radar
     *   APIs. This function will process the messages recieved from the AR12xx
     *   sensor and should be executed in a different task context.
     */
    UInt32                     stopRadarDevTsk;
    /**< Flag to come out of the radar task */
    UInt32                     pauseRadarDevTsk;
    /**< Flag to pause the radar task */
    BspOsal_IntrHandle         intrHandle[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< GPIO Interrupt Handler */
    rlClientCbs_t              rlApp_ClientCtx;
    /**< Application call backs used by the mmwavedfp library */
    GIO_Handle                 uartTxHandle[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< UART Transmit Handle for flashing the AR12 firmware */
    GIO_Handle                 uartRxHandle[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< UART Recieve Handle for flashing the AR12 firmware */
    Int32                      uartDevMap[BSP_AR12XX_NUM_UART_INST];
    /**< UART Map for which device uses which UART instance. The index is the
     *   UART Index.
     */
    UInt32                     arDeviceRevision;
    /**< Device revision of the AR12 device connected to the TDA device */
    Bsp_AR12xxConnType         arConnType;
    /**< Connection Type of AR12 device to TDA device */
    Bsp_Ar12xxMonAppCb         monAppCallBack;
    /**< Application call back when monitorring async event recieved */
    UInt32                     messageId;
    /**< Message Id of the queue */
    UInt32                     triggerType[BSP_AR12XX_MAX_DEVICES_SUPPORTED];
    /**< State of the trigger types for the different devices */
} Bsp_ar12xxObj;

/**
 * \brief   AR12XX File type to be downloaded.
 */
typedef enum Bsp_a12xxSectionDwldType_t
{
    BSP_AR12XX_SECTIONTYPE_BSS_BUILD = 0U,
    /**< BSS_BUILD File type */
    BSP_AR12XX_SECTIONTYPE_CALIB_DATA,
    /**< Calibration data File type */
    BSP_AR12XX_SECTIONTYPE_CONFIG_INFO,
    /**< Configuration information file type */
    BSP_AR12XX_SECTIONTYPE_MSS_BUILD,
    /**< MSS_BUILD file type */
	BSP_AR12XX_SECTIONTYPE_META_IMAGE
	/**< Meta image file type */
} Bsp_a12xxSectionDwldType;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** BSP Driver AR12xx radar object */
extern Bsp_ar12xxObj       gBspAr12xxObj;

/** Constant list of the sensors supported by the radar driver */
extern Bsp_ar12xxSensorObj gBspAr12xxSensorCfgList[
    BSP_AR12XX_MAX_CONFIG_SUPPORTED];

/**< \brief Sensor configuration for the AR1243 Radar Sensor  */
extern Bsp_Ar12xxConfigObj gAr1243RadarConfig;
/**< \brief Sensor monitorring configuration for the AR1243 Radar Sensor  */
extern Bsp_Ar12xxMonConfigObj gAr1243RadarMonConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Function to initialize the #Bsp_ar12xxConfigObj structure.
 *
 *  \param  radarConfigName  Name of the sensor which will determine the
 *                           parameters.
 *
 *  \return None.
 */
void Bsp_ar12xxConfigObj_Init(char radarConfigName[]);

/**
 *  \brief  SPI Open Callback registered with the radar interface
 *
 *  \param  deviceIndex     This is the deviceIndex communication interface to
 *                          open.
 *  \param  flags           Flags to configure the interface.
 *
 *  \return rlComIfHdl_t    Handle to access the communication interface
 */
rlComIfHdl_t Bsp_ar12xxSpiOpenCb(rlUInt8_t deviceIndex,
                                 UInt32    flags);

/**
 *  \brief  SPI Close Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *
 *  \return retVal Success - BSP_SOK, Failure - BSP_EFAIL
 */
Int32 Bsp_ar12xxSpiCloseCb(rlComIfHdl_t fd);

/**
 *  \brief  SPI Read Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *  \param  pBuff  Buffer to store data from communication interface
 *  \param  len    Read size in bytes
 *
 *  \return retVal Length of received data
 */
Int32 Bsp_ar12xxSpiReadCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len);

/**
 *  \brief  SPI Write Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *  \param  pBuff  Buffer to store data from communication interface
 *  \param  len    Read size in bytes
 *
 *  \return retVal Length of received data
 */
Int32 Bsp_ar12xxSpiWriteCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len);

/**
 *  \brief  BSP wrapper to set the mask for the SPI.
 *
 *  \param  fd     Radar device handle.
 *
 *  \return None
 */
void Bsp_ar12xxGpioIRQMaskCb(rlComIfHdl_t fd);

/**
 *  \brief  BSP wrapper to clear the mask for the SPI.
 *
 *  \param  fd     Radar device handle.
 *
 *  \return None
 */
void Bsp_ar12xxGpioIRQUnMaskCb(rlComIfHdl_t fd);

/**
 *  \brief  Function to initialize the GPIO Parameters.
 *
 *  \param  pObj    Pointer to the radar driver object.
 *
 *  \return retVal  Returns BSP_SOK if the GPIO intance id is correctly
 *                  provided by the caller and the GPIO has been initialized
 *                  successfully.
 */
Int32 Bsp_ar12xxGpioInit(const Bsp_ar12xxObj *pObj);

/**
 *  \brief  BSP wrapper to power on the radar device.
 *
 *  \param  deviceIndex     Radar device index.
 *
 *  \return retVal          BSP_SOK is returned.
 */
Int32 Bsp_ar12xxGpioPowerOnDeviceCb(rlUInt8_t deviceIndex);

/**
 *  \brief  BSP wrapper to power on the satellite radar device.
 *
 *  \param  deviceIndex     Radar device index.
 *
 *  \return retVal          BSP_SOK is returned.
 */
Int32 Bsp_ar12xxFPDPowerOnDeviceCb(rlUInt8_t deviceIndex);

/**
 *  \brief  BSP wrapper to power off the radar device.
 *
 *  \param  deviceIndex     Radar device index.
 *
 *  \return retVal          BSP_SOK is returned.
 */
Int32 Bsp_ar12xxGpioPowerOffDeviceCb(rlUInt8_t deviceIndex);

/**
 *  \brief  BSP wrapper to read the status of the GPIO pin.
 *
 *  \param  fd              Radar device handle.
 *
 *  \return gpioPinValue    1 or 0 depending on the value of the GPIO pin.
 */
Int32 Bsp_ar12xxGpioPinReadCb(rlComIfHdl_t fd);

/**
 *  \brief  BSP wrapper to register the GPIO interrupt with the CPU.
 *
 *  \param  deviceIndex     Radar device index.
 *  \param  pHandler        A radar interface function which will be called
 *                          from the ISR routine context.
 *  \param  pValue          Dummy parameter NULL value sent from the radar
 *                          interface functions.
 *
 *  \return gpioPinValue    1 or 0 depending on the value of the GPIO pin.
 */
Int32 Bsp_ar12xxGpioIntrRegisterCb(UInt8              deviceIndex,
                                   RL_P_EVENT_HANDLER pHandler,
                                   void              *pValue);
/**
 *  \brief  BSP wrapper to program the SOP GPIO lines.
 *
 *  \param  deviceIndex     Radar device index.
 *  \param  sopMode         Sense on Power Mode. Valid values are:
 *                          0b101 (SOP mode 5)= Flash programming
 *                          0b001 (SOP mode 4) = Functional mode
 *                          0b011 (SOP mode 2) = Dev mode
 *
 *  \return retVal          BSP_SOK if the SOP is programmed correctly.
 *                          BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxGpioConfigSoP(UInt32 sopMode, UInt8 deviceIndex);

/**
 *  \brief  BSP wrapper to wait for the Host IRQ line to go High or low
 *
 *  \param  fd              Radar device handle.
 *  \param  highLow         Parameter for waiting for High or waiting for Low.
 *
 *  \return retVal          BSP_SOK if the host Irq has gone High or Low.
 *                          BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxGpioWaitHostIrqLow(rlComIfHdl_t fd, UInt8 highLow);

/**
 *  \brief  Function to power on the radar device.
 *
 *  \return retVal  Returns BSP_SOK if the radar device has powered up properly
 *                  and in a timeout interval. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxRadarDeviceOn(void);

/**
 *  \brief  Function to register the different call backs.
 *
 *  \return retVal  Always BSP_SOK
 */
Int32 Bsp_ar12xxRegisterCallbacks(void);

/**
 *  \brief  Function to download the firmware to the radar device via SPI.
 *
 *  \return retVal  Returns BSP_SOK if the firmware is downloaded properly and
 *                  BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxFmwSpiDwld(void);

/**
 *  \brief  Function to run the firmware to the radar device.
 *
 *  \return retVal  Returns BSP_SOK if the radar initial code has run properly
 *                  and in a timeout interval. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxFmwRun(void);

/**
 *  \brief  Function to print the version of the radar sensor driver.
 *
 *  \return retVal  Returns BSP_SOK if the driver version is read correctly.
 *                  BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxPrintVersion(void);

/**
 *  \brief  Function to configure the profile parameters of the radar sensor.
 *
 *  \param  radarConfigIdx  Configuration index of the radar to pick up the
 *                          default parameters that need to be programmed to the
 *                          radar sensor.
 *
 *  \return retVal  Returns BSP_SOK if the profile parameters are configured
 *                  correctly. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxConfigProfile(UInt32 radarConfigIdx);

/**
 *  \brief  Function to create the semaphore and task used for communicating
 *          with the radar sensor.
 *
 *  \return retVal  Returns BSP_SOK if the semaphore and task are created
 *                  correctly. BSP_EFAIL is returned otherwise.
 */
Int32 Bsp_ar12xxCreateCommInfra(void);

/**
 *  \brief  BSP OSAL wrapper to interface with the radar callbacks for
 *          Semaphore create.
 *
 *  \param  pLockObj    Semaphore Lock Handle.
 *  \param  name        Name of the Semaphore Handle. Note that this parameter
 *                      is currently not in use.
 *
 *  \return retVal      Success or Failure status of creating the semaphore.
 */
Int32 Bspdrv_A12xxSemObjCreateCb(void **pLockObj, Char *name);

/**
 *  \brief  BSP OSAL wrapper to interface with the radar callbacks for
 *          Semaphore pend.
 *
 *  \param  pLockObj    Semaphore Lock Handle.
 *  \param  timeout     Timeout for which the semaphore should pend.
 *
 *  \return retVal      Success or Failure status of pending on the semaphore.
 */
Int32 Bsp_ar12xxSemObjWaitCb(void **pLockObj, UInt32 timeout);

/**
 *  \brief  BSP OSAL wrapper to interface with the radar callbacks for
 *          Semaphore post.
 *
 *  \param  pLockObj    Semaphore Lock Handle.
 *
 *  \return retVal      Success or Failure status of posting the semaphore.
 */
Int32 Bsp_ar12xxSemObjPendCb(void **pLockObj);

/**
 *  \brief  BSP OSAL wrapper to interface with the radar callbacks for
 *          Semaphore delete.
 *
 *  \param  pLockObj    Semaphore Lock Handle.
 *
 *  \return retVal      Success or Failure status of deleting the semaphore.
 */
Int32 Bsp_ar12xxSemObjDeleteCb(void **pLockObj);

/**
 *  \brief  BSP OSAL wrapper to interface with the BspOsal_sleep.
 *
 *  \param  milliSecs   Time to sleep in milliseconds.
 *
 *  \return retVal      BSP_SOK is returned after the sleep duration.
 */
Int32 Bsp_ar12xxSleepCb(UInt32 milliSecs);

/**
 *  \brief  Function to post the semaphore for the returned function to be
 *          run from #Bsp_ar12xxRadarDevTask context.
 *
 *  \param  pEntry  Call back function pointer returned from the
 *                  radar interface.
 *  \param  pValue  Pointer to data passed to function.
 *  \param  flags   Flag to indicate preference.
 *
 *  \return retVal  BSP_OK if the pEntry is successfully registered.
 */
Int32 Bsp_ar12xxRadarTaskPost(BspDrv_ar12xxSpawnCallBack pEntry,
                              const void                *pValue,
                              UInt32                     flags);

/**
 *  \brief  Function to configure the chirp parameters.
 *
 *  \param  radarConfigIdx  Radar Configuration index.
 *
 *  \return retVal  BSP_OK if the chirp is configured.
 */
Int32 Bsp_ar12xxConfigChirp(UInt32 radarConfigIdx);

/**
 *  \brief  Function to find the maximum time to sleep before issuing Dynamic
 *          frame config.
 *
 *  \param  radarConfigIdx  Configuration index of the radar to pick up the
 *                          default parameters that need to be programmed to the
 *                          radar sensor.
 *
 *  \return retVal          BSP_OK if the firmware chunk is downloaded
 *                          successfully. BSP_EFAIL otherwise.
 */
UInt32 Bsp_ar12xxCalcMaxSleepTime(UInt32 radarConfigIdx);

/**
 *  \brief  Function to initialize the UART Parameters.
 *
 *  \param  pObj    Pointer to the radar driver object.
 *
 *  \return retVal  Returns BSP_SOK if the UART intance id is correctly
 *                  provided by the caller and the UART has been initialized
 *                  successfully.
 */
Int32 Bsp_ar12xxUartInit(Bsp_ar12xxObj *pObj);

/**
 *  \brief  Function to connect to the AR12 via UART.
 *
 *  \param  deviceId    Device ID to which the UART is to be connected.
 *                      Should be 0/1/2/3
 *  \param  pObj        Pointer to the radar driver object.
 *
 *  \return retVal  Returns BSP_SOK if the UART intance id is connected.
 *                  BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxUartConnect(UInt32 deviceId, Bsp_ar12xxObj *pObj);

/**
 *  \brief  Function to erase the firmware flash of AR12.
 *
 *  \param  deviceId    Device Index for which the flash has to be erased.
 *  \param  pObj        Pointer to the radar driver object.
 *
 *  \return retVal      Returns BSP_SOK if the flash is successfully erased.
 *                      BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxFmwEraseFlash(UInt32 device, Bsp_ar12xxObj *pObj);

/**
 *  \brief  Function to program firmware flash for AR12.
 *
 *  \param  deviceId    Device Index for which the flash has to be erased.
 *  \param  pObj        Pointer to the radar driver object.
 *  \param  sectionType Type of the section being loaded. For valid values
 *                      refer #Bsp_a12xxSectionDwldType.
 *
 *  \return retVal  Returns BSP_SOK if the flash is successfully flashed.
 *                  BSP_EFAIL otherwise.
 */
Int32 Bsp_ar12xxFmwSectionFlash(UInt32 deviceId, Bsp_ar12xxObj *pObj,
                                UInt32 sectionType);

/**
 *  \brief  Function to configure the BPM parameters.
 *
 *  \param  radarConfigIdx  Radar Configuration index.
 *
 *  \return retVal  BSP_OK if the BPM common parameters is configured.
 */
Int32 Bsp_ar12xxConfigBpmCommon(UInt32 radarConfigIdx);

/**
 *  \brief  Function to configure the BPM chirp parameters.
 *
 *  \param  radarConfigIdx  Radar Configuration index.
 *
 *  \return retVal  BSP_OK if the BPM chirp is configured.
 */
Int32 Bsp_ar12xxConfigBpmChirp(UInt32 radarConfigIdx);

/**
 *  \brief  Function to find what is the version of the AR device
 *          connected to the TDA device
 *
 *  \param  None
 *
 *  \return arDeviceConnected   Revision of the AR device connected.
 *                              1U - ES1.0
 *                              2U - ES2.0
 *                              0U - Default Error if no device detected.
 */
UInt32 Bsp_ar12xxGetDeviceRevision(void);

/** \brief Function to read the acknowledge from AR12.
 *
 *  \param  deviceId    Device Index to read the acknowledgement from.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *
 *  \return retVal  BSP_SOK - If the acknowledge is recieved.
 *                  BSP_EFAIL - Otherwise.
 */
Int32 Bsp_ar12xxUartReadAck(UInt32 deviceId, Bsp_ar12xxObj *pObj);

/** \brief Function to send a packet of data via UART to the AR12xx.
 *
 *  \param  deviceId    Device Index to send the acknowledge data.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *  \param  buffer      Buffer of the data to be sent.
 *  \param  length      Length of the buffer being sent.
 *
 *  \return retVal  BSP_SOK - If the transmit of the packet is successful.
 *                  BSP_EFAIL - Otherwise.
 */
Int32 Bsp_ar12xxUartSendPacket(UInt32         deviceId,
                               Bsp_ar12xxObj *pObj,
                               UInt8         *buffer,
                               UInt32         length);

/** \brief Function to read back the last recieved packet.
 *
 *  \param  pObj    Pointer to the BSP AR12 object.
 *  \param  length  Length of the packet.
 *
 *  \return retVal  BSP_SOK - If the transmit of the start dowload is successful
 *                  BSP_EFAIL - Otherwise.
 */
Int32 Bsp_ar12xxUartRecvPacket(UInt32 deviceId,
                               Bsp_ar12xxObj *pObj,
                               UInt32 length);

/** \brief Function to load and run the firmware of slave devices
 *
 *  \param  none
 *
 *  \return retVal  BSP_SOK - If the slave boot was successful
 *                  BSP_EFAIL - Otherwise.
 */
Int32 Bsp_ar12xxBootSlaves(void);

/** \brief Function to count number of bits set in a number
 *
 *  \param  number  Number to read.
 *
 *  \return count   Number of 1s in the number.
 */
UInt32 Bsp_ar12xxCountBits(UInt32 number);

/**
 *  \brief  I2CtoSPI Bridge Open Callback registered with the radar interface
 *
 *  \param  deviceIndex     This is the deviceIndex communication interface to
 *                          open.
 *  \param  flags           Flags to configure the interface.
 *
 *  \return rlComIfHdl_t    Handle to access the communication interface
 */
rlComIfHdl_t Bsp_spi2cOpenCb(rlUInt8_t deviceIndex,
                             UInt32    flags);

/**
 *  \brief  I2CtoSPI Bridge Close Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *
 *  \return retVal Success - BSP_SOK, Failure - BSP_EFAIL
 */
Int32 Bsp_spi2cCloseCb(rlComIfHdl_t fd);

/**
 *  \brief  I2CtoSPI Bridge Write Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *  \param  pBuff  Buffer to store data from communication interface
 *  \param  len    Read size in bytes
 *
 *  \return retVal Length of received data
 */
Int32 Bsp_spi2cWriteCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len);

/**
 *  \brief  I2CtoSPI Bridge Read Callback registered with the radar interface
 *
 *  \param  fd     Handle to access the communication interface
 *  \param  pBuff  Buffer to store data from communication interface
 *  \param  len    Read size in bytes
 *
 *  \return retVal Length of received data
 */
Int32 Bsp_spi2cReadCb(rlComIfHdl_t fd, UInt8 *pBuff, UInt16 len);

/**
 * \brief Function to select the GPIO based UART selection
 *
 * \param devNum Device Number.
 *
 * \return retVal BSP_SOK if the operation is successful.
 */
Int32 Bsp_ar12xxGpioUartSelect(UInt32 devNum);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_AR12XX_PRIV_H_  */

