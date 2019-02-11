/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \file iss_sensors.h
 *
 * \brief APIs for controlling external sensors.
 *
 *
 *******************************************************************************
 */

#ifndef ISS_SENSORS_H_
#define ISS_SENSORS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/**< This header file depends on some the enums defined in system_const */
#include <include/link_api/system_const.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* Maximum number of channels supported */
#define ISS_SENSORS_MAX_CHANNEL                 (4U)

/* Max char in the sensor name */
#define ISS_SENSORS_MAX_NAME                    (50U)

/* Supports Sensor's name */
#define SENSOR_OMNIVISION_OV10640_CSI2          "OV10640"
#define SENSOR_APTINA_AR0140                    "AR0140"
#define SENSOR_APTINA_AR0132                    "AR0132"
#define SENSOR_SONY_IMX224_CSI2                 "IMX224"
#define SENSOR_OMNIVISION_OV2775_CSI2           "OV2775"
#define SENSOR_OMNIVISION_OV2775_TIDA1130       "OV2775-TIDA1130"
#define SENSOR_APTINA_AR0140_TIDA262            "AR0140-TIDA262"
#define SENSOR_OMNIVISION_OV10640_IMI           "OV10640-IMI"
#define SENSOR_APTINA_AR0143                    "AR0143"
#define SENSOR_APTINA_AR0143_MARS               "AR0143-MARS"
#define SENSOR_SONY_IMX390_UB953_D3             "IMX390-UB953_D3"
#define SENSOR_OMNIVISION_OV10640_OV490_IMI     "OV10640-OV490-IMI"
#define SENSOR_SONY_IMX390_AWR1243_UB953_D3     "IMX390-AWR1243-UB953_D3"
#define SENSOR_APTINA_AR0233_MARS               "AR0233_UB953_MARS"


/* IOCTL Base number */
#define ISS_SENSORS_IOCTL_BASE                  (0x8000U)

/**
 *******************************************************************************
 *
 *   \brief Command to get exposure parameters
 *          When WDR is enabled in the sensor, this command is used to get
 *          the exposure ratio.
 *
 *   \param pExpPrms            Pointer to AEWB Output configuation
 *                              #IssSensor_ExposureParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_GET_EXPOSURE_PARAMS (ISS_SENSORS_IOCTL_BASE + 1u)

/**
 *******************************************************************************
 *
 *   \brief Command to set AE parameters
 *          When AEWB algorithm is running, it requires to change
 *          the AE and analog gain in the sensor runtime.
 *          This command is used for setting AE and analog gain
 *          in the sensor.
 *
 *   \param pAeParms         Pointer to AE configuration
 *                           #IssSensor_AeParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_SET_AE_PARAMS (ISS_SENSORS_IOCTL_GET_EXPOSURE_PARAMS \
     + 1U)

/**
 *******************************************************************************
 *
 *   \brief Command to get DCC configuration from the sensor
 *
 *   \param pDccParms         Pointer to DCC configuration
 *                           #IssSensor_DccParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_GET_DCC_PARAMS (ISS_SENSORS_IOCTL_SET_AE_PARAMS      \
     + 1U)

/**
 *******************************************************************************
 *
 *   \brief Command to initialize AEWB configuration for each sensor
 *          AE and AWB configuration are sensor specific, so keeping it in the
 *          sensor layer.
 *
 *   \param pAewbParms       Pointer to AEWB configuration
 *                           #AlgorithmLink_IssAewbCreateParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_INIT_AEWB_CONFIG (ISS_SENSORS_IOCTL_GET_DCC_PARAMS + \
        1U)

/**
 *******************************************************************************
 *
 *   \brief Command to get ISP configuration from the sensor
 *          H3A and GLBCE modules are not supported in the DCC, so sensor
 *          provides the ISP configuration for these modules.
 *          Will be removed once DCC supports H3A and GLBCE modules
 *
 *   \param pIssParms        Pointer to ISP configuration
 *                           #IssIspConfigurationParameters
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_GET_ISP_CONFIG (ISS_SENSORS_IOCTL_INIT_AEWB_CONFIG + \
        1U)

/**
 *******************************************************************************
 *
 *   \brief Command to Read sensor register
 *          Used for DCC Network tool to read sensor register
 *
 *   \param pReg             Pointer to IssSensor_ReadWriteReg
 *                           #IssSensor_ReadWriteReg
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_READ_REG (ISS_SENSORS_IOCTL_GET_ISP_CONFIG +         \
        1U)

/**
 *******************************************************************************
 *
 *   \brief Command to Write sensor register
 *          Used for DCC Network tool to write sensor register
 *
 *   \param pReg             Pointer to IssSensor_ReadWriteReg
 *                           #IssSensor_ReadWriteReg
 *
 *   \return SYSTEM_STATUS_SOK on success
 *           Error on failure
 *
 *******************************************************************************
 */
#define ISS_SENSORS_IOCTL_WRITE_REG (ISS_SENSORS_IOCTL_READ_REG +              \
        1U)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/*
 *  \brief Enum for Sensor Features
 */
typedef enum
{
    ISS_SENSOR_FEATURE_HFLIP                = 0x1,
    /**< Horizontal Flip feature */
    ISS_SENSOR_FEATURE_VFLIP                = 0x2,
    /**< Vertical Flip feature */
    ISS_SENSOR_FEATURE_EMBEDDED_DATA        = 0x4,
    /**< Embedded extra data in the frame feature */
    ISS_SENSOR_FEATURE_MANUAL_EXPOSURE      = 0x8,
    /**< Support for Manual Exposure */
    ISS_SENSOR_FEATURE_MANUAL_GAIN          = 0x10,
    /**< Support for Manual Gain */
    ISS_SENSOR_FEATURE_LINEAR_MODE          = 0x20,
    /**< Support for Linear Mode output */
    ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE    = 0x40,
    /**< Support for One Pass WDR Mode */
    ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE    = 0x80,
    /**< Support for Two Pass WDR Mode */
    ISS_SENSOR_FEATURE_DCC_SUPPORTED        = 0x100,
    /**< DCC Feature */
    ISS_SENSOR_MAX_FEATURES                 = 0x200,
    /**< Max Features */
    ISS_SENSOR_FEATURE_FORCE32BITS          = 0x7FFFFFFF
    /**< Last enum to make it int32 */
} IssSensor_Features;

/*
 *  \brief Enum for different sensor exposures in WDR sensor
 */
typedef enum
{
    ISS_SENSOR_EXPOSURE_LONG,
    /**< Long Exposure output from sensor */
    ISS_SENSOR_EXPOSURE_SHORT,
    /**< Short Exposure output from sensor */
    ISS_SENSOR_EXPOSURE_VSHORT,
    /**< Very short Exposure output from sensor */
    ISS_SENSOR_MAX_EXPOSURE,
    ISS_SENSOR_EXPOSURE_FORCE32BITS = 0x7FFFFFFF
} IssSensor_Exposures;

/*
 *  \brief For Line Interleaved WDR mode, this structure is used
 *         for specifying position of each exposure frame.
 */
typedef struct
{
    UInt32 totalWidth, totalHeight;
    /**< Total Frame size */
    struct {
        UInt32 startx, starty;
        /**< Start position of the exposure frame */
        UInt32 width, height;
        /**< frame size of the exposure frame */
    } info[ISS_SENSOR_MAX_EXPOSURE];
} IssSensor_LineInterleavedExpFrmInfo;

typedef struct
{
    UInt32 chId;
    /**< Channel Id */
    UInt32 expRatio;
    /**< Exposure ration for WDR output format, not used for linear mode */
    UInt32 exposureTime[ISS_SENSOR_MAX_EXPOSURE];
    /**< Exposure time in ms for all exposure outputs,
         For Linear mode output, only Lonk exposure entry is used */
} IssSensor_ExposureParams;

/*
 *  \brief Structure for setting AE params
 */
typedef struct
{
    UInt32 chId;
    /**< Channel Id */
    UInt32 exposureTime[ISS_SENSOR_MAX_EXPOSURE];
    /**< Exposure time in ms for all exposure outputs,
         For Linear mode output, only Lonk exposure entry is used */
    UInt32 analogGain;
    /**< Analog gain value */
} IssSensor_AeParams;

/*
 *  \brief Structure for setting DCC params
 */
typedef struct
{
    UInt32 chId;
    /**< Channel Id */
    UInt8 *pDccCfg;
    /**< Pointer to DCC config */
    UInt32 dccCfgSize;
    /**< DCC Profile Size */
} IssSensor_DccParams;

/*
 *  \brief Create Time parameters, ISS sensor layer uses these
 *         parameters and configures board module and sensor.
 */
typedef struct
{
    char                            name[ISS_SENSORS_MAX_NAME];
    /**< Name of the sensor */
    UInt32                          enableFeatures[ISS_SENSORS_MAX_CHANNEL];
    /**< Bit mask of the features to be enabled in the sensor */
    UInt32                          fps[ISS_SENSORS_MAX_CHANNEL];
    /**< Sensor output fps */
    System_VideoIfWidth             videoIfWidth[ISS_SENSORS_MAX_CHANNEL];
    /**< Video Interface Width for each channel
         used for specifying number of lanes in CSI2 capture */
    UInt32                          numChan;
    /**< Number of channel in which sensor is to be opened */
    UInt32                          i2cInstId;
    /**< Instance id of the I2c on which this sensor is to be configured */
    UInt8                           i2cAddr[ISS_SENSORS_MAX_CHANNEL];
    /**< I2c address of the each sensor channel */
} IssSensor_CreateParams;

/*
 *  \brief Structure used to read or write sensor registers.
 *         Used by the DCC Tool to read/write sensor registers
 */
typedef struct
{
    UInt32 chId;
    /**< Channel Id */
    UInt16 regAddr;
    /**< Sensor Register Address */
    UInt16 regValue;
    /**< Sensor Register Value */
} IssSensor_ReadWriteReg;

/*
 *  \brief Sensor Information structure
 */
typedef struct
{
    UInt32                              width;
    /**< output width of the sensor  */
    UInt32                              height;
    /**< output height of the sensor  */
    System_VideoDataFormat              dataFormat;
    /**< dataformat of the sensor  */
    System_BitsPerPixel                 bpp;
    /**< Bits per pixel*/

    UInt32                              features;
    /**< Bitwise list of feature supported by the sensor */

    UInt32                              aewbMode;
    /**< AEWB mode */

    UInt32                              ramOffset;
    /**< Offset where DCC profile for this sensor is stored,
         Currently used for specifying QSPI offset */

    UInt32                              maxExp;
    /**< Max Exposure supported for WDR mode, used in #frmInfo */

    IssSensor_LineInterleavedExpFrmInfo lnIntrExpFrmInfo;
    /**< Frame Information for line interleaved output frame */
} IssSensor_Info;

/*******************************************************************************
 *  Functions Declarations
 *******************************************************************************
 */

Void IssSensor_Init(void);

/**
 *******************************************************************************
 *
 * \brief Function to get Sensor information for given sensor
 *        It searches in the table of registered sensors, it returns
 *        information of first sensor, whose name matches with the
 *        given sensor.
 *
 * \params name      [IN]   Name of the sensor
 * \params pInfo     [OUT]  Pointer to sensor information structure
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_GetSensorInfo(char name[], IssSensor_Info *pInfo);

/**
 *******************************************************************************
 *
 * \brief Function to get Sensor information for sensor whose DCC ID is passed.
 *        It searches in the table of registered sensors, it returns
 *        information of first sensor, whose dcc id matches with the given id.
 *        Typically used by the DCC Network handler to get the
 *        sensor information.
 *
 * \params dccId     [IN]   DCC Id of the sensor
 * \params pInfo     [OUT]  Pointer to sensor information structure
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_GetSensorInfoFromDccId(UInt32 dccId, IssSensor_Info *pInfo);

/**
 *******************************************************************************
 *
 * \brief Function to get the sensor handle for the given sensor.
 *        This is used by the DCC Network Handler to Read/Write sensor
 *        register.
 *        Returns sensor handle only if it is opened.
 *
 *
 * \params dccId     [IN]   DCC Id of the sensor
 * \params pInfo     [OUT]  Pointer to sensor information structure
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Ptr IssSensor_GetSensorHandle(char name[]);

/**
 *******************************************************************************
 *
 * \brief Creates the sensor, based on the create params, it
 *        searches for the given sensor in the registered sensors,
 *        configures the board module if sensor supports board
 *        module and creates sensor fvid2 driver.
 *        It also configures sensor in the given WDR mode and also sets
 *        the default output resolution in the sensor.
 *
 * \params pCreatePrms      [IN] Pointer to the create params
 *
 * \return handle to the created sensor
 *         NULL if there is any error
 *
 *******************************************************************************
*/
Ptr IssSensor_Create(IssSensor_CreateParams *pCreatePrms);

/**
 *******************************************************************************
 *
 * \brief Used for sending control commands, this layer
 *        supports all configuration using control commants.
 *        For the list of supported control command, see defines
 *        section of this file.
 *
 *        Must be called after Create function
 *
 * \params handle           [IN]  Handle to the created sensor
 * \params cmd              [IN]  Control command
 * \params cmdArgs          [IN]  Pointer to the command specific arguments.
 * \params cmdRetArgs       [OUT] Pointer to the command specific return arguments
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_Control(Ptr handle, UInt32 cmd, Ptr cmdArgs,
    Ptr cmdRetArgs);

/**
 *******************************************************************************
 *
 * \brief Used Starting the sensor, which is already opened using
 *        Create function.
 *        Must be called after Create function.
 *
 * \params handle       [IN] Handle of the sensor
 * \params chId         [IN] ID of the channel to be started.
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_Start(Ptr handle, UInt32 chId);

/**
 *******************************************************************************
 *
 * \brief Used stopping the sensor, which is alraedy opened using
 *        Create function.
 *        Must be called after Create function.
 *
 * \params handle       [IN] Handle of the sensor
 * \params chId         [IN] ID of the channel to be stopped.
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_Stop(Ptr handle, UInt32 chId);

/**
 *******************************************************************************
 *
 * \brief Used deleting the sensor, which is already opened using
 *        Create function. Internally it deletes sensor's fvid2 driver.
 *        After this call, handle is not valid.
 *
 *        Must be called after Create function.
 *
 * \return SOK in case of success
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensor_Delete(Ptr handle);

/**
 *******************************************************************************
 *
 * \brief Initialize sensor create Parameter
 *
 * \params prms             [IN] Pointer to the sensor create parameters
 *
 *******************************************************************************
*/
static inline Void IssSensor_CreateParams_init(
    IssSensor_CreateParams *prms);

/**
 *******************************************************************************
 *
 * \brief Initialize sensor info with the default parameters
 *
 * \params prms             [IN] Pointer to the sensor create parameters
 *
 *******************************************************************************
*/
static inline Void IssSensor_Info_Init(
    IssSensor_Info *prms);


/*******************************************************************************
 *  Functions definitions
 *******************************************************************************
 */

static inline Void IssSensor_CreateParams_init(
    IssSensor_CreateParams *prms)
{
    UTILS_assert(NULL != prms);

    memset(prms, 0, sizeof(IssSensor_CreateParams));
}

static inline Void IssSensor_Info_Init(
    IssSensor_Info *prms)
{
    UTILS_assert(NULL != prms);

    memset(prms, 0x0, sizeof(IssSensor_Info));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of ISS_SENSORS_H_*/


/*@}*/
