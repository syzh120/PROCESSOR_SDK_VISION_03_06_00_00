/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 * \defgroup BSP_DRV_DEVICE_ULTRASONIC_SENSOR_API_PGA450 PGA450 Ultra-sonic Sensor API
 *
 *  This modules define API specific to PGA450 Ultra-sonic Sensor.
 *
 * @{
 */

/**
 *  \file bsp_pga450.h
 *
 *  \brief PGA450 Ultra-sonic Sensor API
 */

#ifndef BSP_PGA450_H_
#define BSP_PGA450_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Sensor Driver handle. */
typedef Ptr UltraSensor_Handle;

/** \brief Maximum UART driver instance to create at the time of init. */
#define BSP_PGA450_MAX_UART_INST        (1U)

/** \brief At max we can connect 16 device to a single UART. */
#define BSP_PGA450_MAX_DEVICE           (16U)

/**
 *  \brief PGA450 distance mode.
 */
typedef enum
{
    BSP_PGA450_DISTANCE_MODE_SHORT = 0x01U,
    /**< Used for short distance measurement. */
    BSP_PGA450_DISTANCE_MODE_LONG = 0x02U
                                    /**< Used for long distance measurement. */
} Bsp_Pga450DistanceMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Bsp_Pga450InitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32 numUartInst;
    /**< Number of UART instance to create at this driver init. */
    UInt32 uartInstId[BSP_PGA450_MAX_UART_INST];
    /**< UART instance to which the sensor is connected to.
     *   This is used to create UART driver.
     *   Refer UART ID defined in bsp_device.h file.*/
} Bsp_Pga450InitParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/**
 *  \brief PGA450 Ultra-sonic sensor driver init function.
 *
 *  Initializes the PGA450 driver.
 *  This function should be called before calling any of sensor API's and
 *  should be called only once. Also this API should be called after
 *  initializing UART driver.
 *
 *  \param initPrms     [IN] Pointer to the init parameter containing
 *                           instance specific information
 *
 *  \return BSP_SOK on success else appropriate BSP error code on failure.
 */
Int32 Bsp_pga450Init(const Bsp_Pga450InitParams *initPrms);

/**
 *  \brief PGA450 Ultra-sonic sensor driver deinit function.
 *
 *  Uninitializes the PGA450 driver and deletes the UART driver and should be
 *  called during system shutdown.
 *  Should not be called if Bsp_pga450Init() is not called.
 *
 *  \return BSP_SOK on success, else appropriate BSP error code on failure.
 */
Int32 Bsp_pga450DeInit(void);

/**
 *  \brief Probes an UART bus for a specific device slave address.
 *
 *  \param uartInstId   [IN] UART instance to which the sensor is connected to.
 *                           Refer UART ID defined in bsp_device.h file.
 *  \param deviceId     [IN] Sensor device ID.
 *
 *  \return BSP_SOK device found, else device not detected.
 */
Int32 Bsp_pga450ProbeDevice(UInt32 uartInstId, UInt8 deviceId);

/**
 *  \brief Starts the distance measurement, receives the measured data and
 *  converts the measured data and returns in cm.
 *
 *  \param uartInstId   [IN] UART instance to which the sensor is connected to.
 *                           Refer UART ID defined in bsp_device.h file.
 *  \param deviceId     [IN] Sensor device ID.
 *  \param distMode     [IN] Distance mode.
 *                           Refer #Bsp_Pga450DistanceMode for valid values.
 *
 *  \return Returns the measured data in cm. Returns negative value in case of
 *   error (RX error, checksum error) or timeout.
 */
Int32 Bsp_pga450GetMeasurement(UInt32 uartInstId,
                               UInt8  deviceId,
                               UInt8  distMode);

/**
 *  \brief Bsp_Pga450InitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_Pga450InitParams structure.
 *
 */
static inline void BspPga450InitParams_init(Bsp_Pga450InitParams *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspPga450InitParams_init(Bsp_Pga450InitParams *initPrms)
{
    UInt32 cnt;

    if (NULL != initPrms)
    {
        initPrms->numUartInst = 1U;
        for (cnt = 0U; cnt < BSP_PGA450_MAX_UART_INST; cnt++)
        {
            initPrms->uartInstId[cnt] = 0U;
        }

        /* Default to UART10 */
        initPrms->uartInstId[0U] = BSP_DEVICE_UART_INST_ID_9;
    }

    return;
}

#ifdef __cplusplus
}
#endif  /* #ifndef BSP_PGA450_H_ */

#endif

/* @} */
