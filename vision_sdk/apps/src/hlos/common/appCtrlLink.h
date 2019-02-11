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
 *  \ingroup LINK_API
 *  \defgroup APP_CTRL_LINK_API Application Control link
 *
 *  This module defines the control commands that are applicable to
 *  control application specific function when Linux on A15.
 *
 *  When Linux runs on A15, IPU1-0 still needs to control some board level
 *  devices like capture sensors
 *
 *  This link implemented on IPU1-0 exports APIs which application on A15
 *  can invoke to control these devices
 *
 *  This API is only valid when Linux runs on A15
 *
 *  This is control ONLY link, i.e is does not take any buffers as input
 *  or output.
 *
 *   @{
*/

/**
 *******************************************************************************
 *
 *  \file appCtrlLink.h
 *  \brief Application Control link
 *
 *******************************************************************************
*/

#ifndef _APP_CTRL_LINK_H_
#define _APP_CTRL_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>

#include <src/include/chains_common_srv_calib.h>
#include <src/include/chains_common_sensor.h>
#include <src/rtos/iss/include/app_util_iss.h>

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
#define KID_FAIL                            (0xFF)

/* RVP board I2C addresses */
#define KTCA9539_I2CADDR_BASEBOARD          (0x75U)
#define KTCA9539_I2CADDR_BASEBOARD_REV1     (0x76U)
#define KTCA9539_I2CADDR_SOM                (0x74U)

typedef struct {
    UInt8 boardIdSOM;
    UInt8 boardIdBaseboard;
} AppCtrl_BoardIds;

/**
 *******************************************************************************
 * \brief Params for command APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED
 *******************************************************************************
 */
typedef struct {

    UInt32 isConnected;
    /**< [OUT]
         TRUE: Multi-des board is connected,
         FALSE: Multi-des board is NOT connected
     */

} AppCtrlCmd_BoardIsMultiDesConnectedPrm;

/**
 *******************************************************************************
 * \brief Params for command APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED
 *
 *        MOST parameters are set based on how the connections are done on
 *        the board, limited control is given from A15 side
 *
 *******************************************************************************
 */
typedef struct {

    Chains_CaptureSrc captureSrcId;
    /**< Sensor ID */

    UInt32 isLVDSCaptMode;
    /**< [IN]
     *    TRUE: OV1063X Multi-CH LVDS capture mode
     *    FALSE: OV1063X single channel capture mode
     */

    UInt32 numLvdsCh;
    /**< [IN] Number of channels of LVDS to configure
     *        Valid values 1..6
     */
    AppUtils_Obj issUtilObj;
    /**< [IN] ISS utils OBJ */
} VideoSensorCreateAndStartAppPrm;

typedef struct {
    AppUtils_Obj                        issSensorInfo;
    /**< [IN] ISS utils OBJ,
              Input Parameter
              Used for getting sensor informatin and then
              initializing capture/isp/simcom AEWB parameters */

    UInt32                              issCaptLinkId;
    /**< ISS Capture Link Id,
         ISS Capture Link params initialized only if set to valid link id
         If set to SYSTEM_LINK_ID_INVALID, ISS Capture Link parameters
         will not be initialized */
    IssCaptureLink_CreateParams         issCaptLinkPrms;
    /**< ISS Capture Link Create Params to be initialized */

    UInt32                              issIspLinkId;
    /**< ISS ISP Link Id,
         ISS ISP Link params initialized only if set to valid link id
         If set to SYSTEM_LINK_ID_INVALID, ISS ISP Link parameters
         will not be initialized */
    IssM2mIspLink_CreateParams          issIspLinkPrms;
    /**< ISS ISP Link Create Params to be initialized */

    UInt32                              issSimcopLinkId;
    /**< ISS Simcop Link Id,
         ISS Simcop Link params initialized only if set to valid link id
         If set to SYSTEM_LINK_ID_INVALID, ISS Simcop Link parameters
         will not be initialized */
    IssM2mSimcopLink_CreateParams       issSimcopLinkPrms;
    /**< ISS Simcop Link Create Params to be initialized */

    UInt32                              issAewbLinkId;
    /**< ISS AEWB Link Id,
         ISS AEWB Link params initialized only if set to valid link id
         If set to SYSTEM_LINK_ID_INVALID, ISS AEWB Link parameters
         will not be initialized */
    AlgorithmLink_IssAewbCreateParams   issAewbLinkPrms;
    /**< ISS AEWB Link Create Params to be initialized */
} AppCtrl_IssParams;

typedef struct
{
    UInt8   *pDccBuf;
    UInt32  bufSize;
} AppCtrl_IssDccParams;

typedef struct
{
    UInt8   *pConfigBuf;
    UInt32  bufSize;
} AppCtrl_RadarConfigFileParams;

#define MAX_NUM_FILES  16U

typedef struct
{
    AppCtrl_RadarConfigFileParams fileParams[MAX_NUM_FILES];
    UInt32  numFiles;
} AppCtrl_RadarConfigFiles;

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup APP_CTRL_LINK_API_CMD  Application Control link Control Commands

    @{
*/

/**
 *******************************************************************************
 * \brief Link CMD: Command to enable USB port for charging
 *
 * \param NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_BOARD_ENABLE_USB_CHARGING         (0x1002)

/**
 *******************************************************************************
 * \brief Link CMD: Command to check if Multi-des board is connectoed or not
 *
 * \param  AppCtrlCmd_BoardIsMultiDesConnectedPrm *pPrm [OUT]
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED      (0x1003)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set DMM priorities
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES                (0x1004)

/**
 *******************************************************************************
 * \brief Link CMD: Command to perform surround view calibrtaion + QSPI storage
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SURROUNDVIEW_CALIBRATION          (0x1005)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set stat collector init
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT               (0x1006)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set stat collector deinit
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT             (0x1007)

/**
 *******************************************************************************
 * \brief Link CMD: Command to create and start Video sensor
 *
 *   \param VideoSensorCreateAndStartAppPrm *pPrm [IN]
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START     (0x1008)

/**
 *******************************************************************************
 * \brief Link CMD: Command to stop and delete Video Sensor
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE      (0x1009)

/**
 *******************************************************************************
 * \brief Link CMD: Command to Initialize ISS Capture Params
 *                  for the given sensor
 *
 *   \param  pointer to AppCtrl_IssParams
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_INIT_ISS_PARAMS                   (0x100a)

/**
 *******************************************************************************
 * \brief Link CMD: Command to createCAL based sensor
 *                  Created a separate control command so that ISS usecases
 *                  can use sensorInfo instance from the AppCtrl_IssParams
 *                  structure directly.
 *
 *   \param  pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_ISS_SENSOR_CREATE                 (0x100b)

/**
 *******************************************************************************
 * \brief Link CMD: Command to start CAL based sensor
 *                  Created a separate control command so that ISS usecases
 *                  can use sensorInfo instance from the AppCtrl_IssParams
 *                  structure directly.
 *
 *   \param  pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_ISS_SENSOR_START       (0x100c)

/**
 *******************************************************************************
 * \brief Link CMD: Command to stop and delete CAL based sensor
 *                  Created a separate control command so that ISS usecases
 *                  can use sensorInfo instance from the AppCtrl_IssParams
 *                  structure directly.
 *
 *   \param  pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_ISS_SENSOR_STOP_AND_DELETE        (0x100d)

/**
 *******************************************************************************
 * \brief Link CMD: Command to Set the Default Configuration in ISP/Simcop
 *                  link. It gets the default config from ISS Sensor layer
 *                  and then overwrites ISP config from DCC parser output and
 *                  then sets it in the ISP/Simcop links.
 *
 *   \param  pointer to AppCtrl_IssParams
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_ISS_DEFAULT_CONFIG                (0x100e)

/**
 *******************************************************************************
 * \brief Link CMD: Command to Set Board muxes for the given sensor.
 *
 *   \param  pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SET_BOARD_MUXES                   (0x100f)

/**
 *******************************************************************************
 * \brief Link CMD: Command to Set Board muxes for the given sensor.
 *
 *   \param  pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_ENABLE_CSI_OUTPUT                (0x1010)

/**
 *******************************************************************************
 * \brief Link CMD: Command to parse and set the DCC config in ISP
 *
 *   \param pointer to AppUtils_Obj
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_PARSE_AND_SET_SENSOR_DCC          (0x1011)

/**
 *******************************************************************************
 * \brief Link CMD: Command to parse and set the DCC config in ISP
 *
 *   \param pointer to AppCtrl_IssDccParams
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_PARSE_AND_SET_DCC                 (0x1012)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set board IDs read from I2C
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SET_BOARD_IDS                     (0x1013)

#define APP_CTRL_LINK_CMD_LINUX_INIT_COMPLETE               (0x1014)

/**
 *******************************************************************************
 * \brief Link CMD: Command to boot and config Radar (AWR1243)
 *
 *   \param  pointer to ChainsCommon_Ar12xxConfigOut
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_INIT_RADAR                       (0x1015)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set IssCapture Link Params for Radar (AWR1243)
 *
 *   \param  pointer to IssCaptureLink_Params
 *           pointer to ChainsCommon_Ar12xxConfigOut
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SET_RADAR_CAPTURE_PARAM          (0x1016)

/**
 *******************************************************************************
 * \brief Link CMD: Command to start Radar (AWR1243)
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_START_RADAR                       (0x1017)

/**
 *******************************************************************************
 * \brief Link CMD: Command to stop Radar (AWR1243)
 *
 *   \param  pointer to ChainsCommon_Ar12xxConfigOut
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_STOP_RADAR                        (0x1018)

/*@}*/


/**
 *******************************************************************************
 *
 * \brief Set defaults for creation time parameters
 *
 * \param  pPrm [OUT] Create parameters for capture link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void AppCtrlLink_IssParams_Init(AppCtrl_IssParams *pPrms)
{
    if (NULL != pPrms)
    {
        memset(pPrms, 0, sizeof(AppCtrl_IssParams));

        pPrms->issCaptLinkId = SYSTEM_LINK_ID_INVALID;
        pPrms->issIspLinkId = SYSTEM_LINK_ID_INVALID;
        pPrms->issSimcopLinkId = SYSTEM_LINK_ID_INVALID;
        pPrms->issAewbLinkId = SYSTEM_LINK_ID_INVALID;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
