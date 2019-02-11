/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 * \file   stw_board.h
 *
 * \brief  This file contains the APIs that abstract the board-specific details
 *         for StarterWare.
 * The key functionality of this module includes:
 * - Abstraction out of board specific information through APIs
 * - Auto-detection of board, including getting information about board type
 * - Definition of board specific data including:
 *   - Pinmux data
 *   - Clock source information
 *   - On-board devices list, including i2c information
 *   - IP instance availability on board
 *   - Board-level mux, power, IO expanders
 *
 * The Board module needs to be initialized before it can be used.
 *
 * The usual functions called would be:
 * #BOARDInit
 * #BOARDGetId
 *
 * To get information about connected devices in order to control them:
 * #BOARDIsDevicePresent
 * #BOARDGetDeviceCtrlModId
 * #BOARDGetDeviceCtrlModInstNum
 * #BOARDGetDeviceCtrlInfo
 * #BOARDGetDeviceDataModId
 * #BOARDGetDeviceDataModInstNum
 *
 */

#ifndef STW_BOARD_H_
#define STW_BOARD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* ifdef __cplusplus */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Invalid ID  */
#define BOARD_INVALID_ID                (0xFFFFFFFFU)
/** \brief Invalid instance number  */
#define BOARD_INVALID_INST_NUM          (0xFFFFFFFFU)
/** \brief Invalid information  */
#define BOARD_INVALID_INFO              (0xFFFFFFFFU)
/** \brief Invalid instance ID. */
#define BOARD_INVALID_INST_ID           (0xFFU)

/**
 *  \brief EVM Board ID.
 */
typedef enum
{
    BOARD_UNKNOWN = 0x0001U,
    /**< Unknown board. */
    BOARD_VS = 0x0002U,
    /**< Video survillance based board. */
    BOARD_VC = 0x0004U,
    /**< Video conferencing based board. */
    BOARD_VISION = 0x0008U,
    /**< Vision board of TDA2XX family. */
    BOARD_VISION_TI81XX = 0x0010U,
    /**< Vision board of TI81XX family. */
    BOARD_CATALOG = 0x0020U,
    /**< TVP7002/SIL1161A. */
    BOARD_CUSTOM = 0x0040U,
    /**< Any other custom board. */
    BOARD_JAMR3 = 0x0080U,
    /**< JAMR3 board of TDA2XX family. */
    BOARD_MULTIDES = 0x0100U,
    /**< Multi Deserializer board of TDA2XX family. */
    BOARD_BASE_TDA2XX = 0x0200U,
    /**< TDA2XX Base Board. */
    BOARD_BASE_TDA3XX = 0x0400U,
    /**< TDA3XX Base Board. */
    BOARD_BASE_TI81XX = 0x0800U,
    /**< TI81XX Base Board. */
    BOARD_BASE_TDA2EX = 0x1000U,
    /**< TDA2EX Base Board. */
    BOARD_BASE_TDA2PX = 0x2000U,
    /**< TDA2PX Base Board. */
    BOARD_MAX = 0xFFFFU
                /**< Max board ID. */
} boardId_t;

/**
 *  \brief Board revision ID.
 */
typedef enum
{
    BOARD_REV_UNKNOWN = 0x0000U,
    /**< Unknown/unsupported board revision. */
    BOARD_REV_A,
    /**< Board revision A. */
    BOARD_REV_B,
    /**< Board revision B. */
    BOARD_REV_C,
    /**< Board revision C. */
    BOARD_REV_MAX
    /**< Max board revision. */
} boardRev_t;

/**
 *  \brief Device specific modes
 */
typedef enum
{
    BOARD_MODE_DEFAULT,
    /**< This enum could be passed if the mode is a don't care and the
     *   mode select function returns success after selecting the default
     *   mode (if applicable). */
    BOARD_MODE_VIDEO_24BIT,
    /**< 24-bit video mode. */
    BOARD_MODE_VIDEO_16BIT,
    /**< 16-bit video mode. */
    BOARD_MODE_VIDEO_14BIT,
    /**< 14-bit video mode. */
    BOARD_MODE_VIDEO_12BIT,
    /**< 12-bit video mode. */
    BOARD_MODE_VIDEO_10BIT,
    /**< 10-bit video mode. */
    BOARD_MODE_VIDEO_8BIT,
    /**< 8-bit video mode. */
    BOARD_MODE_VIDEO_8BIT_TDM,
    /**< 8-bit TDM (RGB interleaved) video mode. */
    BOARD_MODE_VIDEO_BT656,
    /**< 8-bit BT656 video mode. */
    BOARD_MODE_VIDEO_BT1120,
    /**< 16-bit BT1120 video mode. */
    BOARD_MODE_MAX
    /**< Max board modes. */
} boardMode_t;

/**
 *  \brief Function pointer typedef for custom board initialization
 */
typedef int32_t (*BOARDCustomInitFxn)(void);

/**
 *  \brief Function pointer typedef for device select function per board.
 */
typedef int32_t (*BOARDSelectDeviceFxn)(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief Function pointer typedef for custom board select mode
 */
typedef int32_t (*BOARDSelectModeFxn)(uint32_t    devDrvId,
                                      uint32_t    instId,
                                      boardMode_t boardMode);

/**
 *  \brief Function pointer typedef for device reset function per board.
 */
typedef int32_t (*BOARDResetDeviceFxn)(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief Function pointer typedef for device power on function per board.
 */
typedef int32_t (*BOARDPowerOnDeviceFxn)(uint32_t devId,
                                         uint32_t devInstNum,
                                         uint32_t powerOn);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief Board specific per instance I2C related data.
 */
typedef struct boardI2cInstData
{
    LLD_Hsi2cInstId_t instId;
    /**< I2C controller number. */
    uint32_t          baseAddr;
    /**< I2C peripheral base address. */
    uint32_t          intNum;
    /**< I2C Interrupt number. */
    lld_i2c_busspeed  busClkKHz;
    /**< I2C bus clock in KHz. */
} boardI2cInstData_t;

/**
 *  \brief Board specific data.
 */
typedef struct boardI2cData
{
    uint32_t            numInst;
    /**< Number of I2C instance to initialize. */
    boardI2cInstData_t *pInstData;
    /**< Pointer to #numInst number of I2C board data. */
    uint32_t            probeInstId;
    /**< I2C instance to use for board detect. */
} boardI2cData_t;

/**
 *  \brief Board specific per instance device related data.
 */
typedef struct boardDeviceData
{
    uint32_t              devId;
    /**< Device ID. */
    uint32_t              devInstNum;
    /**< Device instance number - 0 to max-1 in a board. */
    uint32_t              ctrlModId;
    /**<
     * ID of the SoC module to which the device is connected for controlling it.
     * Usually, this will be either I2C, SPI, or GPIO.
     */
    uint32_t              ctrlModInstNum;
    /**<
     * Instance number of the SoC module to which the device is connected for
     * controlling it.
     * Usually, this will be the instance number of I2C, SPI or GPIO on the SoC.
     */
    uint32_t              ctrlInfo;
    /**<
     * Connection information between the SoC module and the device. For example
     * - For I2C, it is the I2C slave address.
     * - For SPI, it is the Chip Select.
     * - For GPIO, it is the GPIO pin number.
     */
    uint32_t              dataModId;
    /**<
     * ID of the SoC module the device has a data connection to.
     * For example, McASP sends data to the codec device. In that case, the
     * dataModId would be set to the ID for McASP.
     */
    uint32_t              dataModInstNum;
    /**<
     * Instance number of the SoC module the device has a data connection to.
     * For example, McASP sends data to the codec device. In that case, the
     * instance number of the McASP would be set as the dataModInstNum.
     */
    BOARDSelectDeviceFxn  pFnSelectDev;
    /**< Select device function pointer. This function will power on the
     *   device, do the device reset sequence and also enable any board level
     *   mux for the provided device. */
    BOARDResetDeviceFxn   pFnResetDev;
    /**< Reset device function pointer. This function will do the device reset
     *   sequence as per the board information. */
    BOARDPowerOnDeviceFxn pFnPowerOnDev;
    /**< Power On device function pointer. This function will do the Powering on
     *   the device as per the board information. */
} boardDeviceData_t;

/**
 *  \brief Structure defining the pin configuration of a board.
 */
typedef struct boardPinmuxBoardCfg
{
    uint32_t moduleId;
    /**< Module ID */
    uint32_t instNum;
    /**< Instance number of the ip */
    uint32_t boardMode;
    /**< Device specific modes */
    uint32_t regOffset;
    /**< Register offset */
    uint32_t regVal;
    /**< Register value */
}boardPinmuxBoardCfg_t;

/**
 *  \brief Board specific data.
 */
typedef struct boardData
{
    uint32_t                     numDev;
    /**< Number of devices connected to the board. */
    const boardDeviceData_t     *pDevData;
    /**< Pointer to #numDev number of device data. */
    const boardPinmuxBoardCfg_t *pPinmuxData;
    /**< Pointer to #boardPinmuxBoardCfg_t data. */
} boardData_t;

/**
 *  \brief Custom board parameters
 */
typedef struct
{
    const char           *brdIdString;
    /**< Custom board ID string. Note: This can't be NULL */
    const char           *brdRevString;
    /**< Custom board revision string. Note: This can't be NULL */
    const boardI2cData_t *i2cData;
    /**< Custom board I2C data. Note: This can't be NULL */
    const boardData_t    *brdData;
    /**< Custom board device data. Note: This can't be NULL */
    BOARDCustomInitFxn    initFxn;
    /**< Custom board initialization function. This can be NULL is no init is
     *   required for custom board */
    BOARDSelectModeFxn    selectModeFxn;
    /**< Custom board select mode function. This can be NULL is no mode select
     *   is required for custom board */
} boardCustomData_t;

/**
 *  \brief Board initialization parameters.
 */
typedef struct boardInitParams
{
    boardId_t          boardId;
    /**< Override board ID detection. Set this to #BOARD_MAX to allow
     *   auto detection of the board connected. Setting any other value will
     *   override the auto detect and force the board ID to the supplied
     *   value.
     *   Allowed values are from enum #boardId_t, or #BOARD_MAX
     */
    boardRev_t         baseBoardRev;
    /**< Override base board revision detection. Set this to #BOARD_REV_MAX
     *   to allow auto detection of base board revision. Setting any other
     *   value will override the auto detect and force the revision to the
     *   supplied value.
     *   Allowed values are from enum #boardRev_t, or #BOARD_REV_MAX
     */
    boardRev_t         dcBoardRev;
    /**< Override daughter card board revision detection. Set this to
     *   #BOARD_REV_MAX to allow auto detection of DC board revision.
     *   Setting any other value will override the auto detect and force
     *   the revision to the supplied value.
     */
    boardCustomData_t *customData;
    /**< Override auto-detection and calling of built in board support functions
     *   and data with custom board implementation. Set to NULL if not used.
     *   Note: When this param is set, boardId, baseBoardRev and dcBoardRev
     *   should be set valid values other than BSP_BOARD_MAX/BSP_BOARD_REV_MAX
     *   so that the board module doesn't do auto-detect.
     */
    uint32_t           isDefPinMuxSettingReq;
    /**< Default Pinumx setting is requried or not. */
} boardInitParams_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Initialize the underlying board. Based on the type of SoC and board,
 *          this function does software initializations required for the current
 *          board. It does not actually do any initialization at the hardware
 *          level.
 *
 *  \param  pInitPrms   Board Initialization parameters. If passed as NULL,
 *                      default parameters are internally used.
 *                      Parameter pInitPrms is of type #boardInitParams_t
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t BOARDInit(const boardInitParams_t *pInitPrms);

/**
 *  \brief  De-init the underlying board. It performs any software level
 *          cleanup for the board module if required.
 *
 *  \param  args        Not used currently. Set to NULL.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t BOARDDeInit(void *args);

/**
 *  \brief  Probes and returns board ID. Usually the board data is read from
 *          EEPROM device.
 *
 *  \return Board_ID        On success
 *  \return BOARD_UNKNOWN   On failure, or if board ID is not known.
 *                          The following cases can potentially cause this
 *                          value to be returned:
 *                          - EEPROM device not connected / not ready
 *                          - Board information not present within EEPROM
 *                          - Board information in EEPROM does not match
 *                            known boards.
 */
boardId_t BOARDGetId(void);

/**
 *  \brief  Function to get the name of the board in printable string.
 *
 *  \return Board_name  Returns a const pointer to the name. If the board is
 *                      not known, then it returns the string as "UNKNOWN".
 */
const char *BOARDGetBoardName(void);

/**
 *  \brief  Returns the base board revision.
 *
 *  \return Base_board_revision On success, returns the base board revision.
 *                              Based on the type of board, the revision
 *                              value returned needs to be interpreted.
 *  \return BOARD_REV_UNKNOWN   On failure, or if board rev ID is not known.
 *                              The following cases can potentially cause this
 *                              value to be returned:
 *                              - EEPROM device not connected / not ready
 *                              - Board information not present within EEPROM
 *                              - Board information in EEPROM does not match
 *                                known boards.
 */
boardRev_t BOARDGetBaseBoardRev(void);

/**
 *  \brief  Function to get the name of the base board revision in printable
 *          string.
 *
 *  \return Board_rev_string    Returns a const pointer to the string. If the
 *                              board revision is not known, then it returns the
 *                              string as "UNKNOWN".
 */
const char *BOARDGetBaseBoardRevName(void);

/**
 *  \brief  Returns the add-on or daughter card board revision.
 *
 *  \return DC_Revision     On success, returns the add-on or daughter card
 *                          revision. Based on the type of board, the revision
 *                          value returned needs to be interpreted.
 */
boardRev_t BOARDGetDcRev(void);

/**
 *  \brief  Function to get the name of the daughter card revision in printable
 *          string.
 *
 *  \return Board_dcrev_string  Returns a const pointer to the string. If the
 *                              board daughter card revision is not known, then
 *                              it returns the string as "UNKNOWN".
 */
const char *BOARDGetDcRevName(void);

/**
 *  \brief  Returns I2C data.
 *
 *  \return Board_I2C_Data      Board I2C data on success
 *  \return NULL                On Failure
 */
const boardI2cData_t *BOARDGetI2cData(void);

/**
 *  \brief  Returns board specific data.
 *
 *  \return Board_Data          Board data on success
 *  \return NULL                On Failure
 */
const boardData_t *BOARDGetData(void);

/**
 *  \brief  Returns the ID of the SoC module to which the device is connected
 *          for controlling it. Usually, this will be either I2C, SPI, or GPIO.s
 *
 *  \param  devId        Device ID to get the information for.
 *  \param  devInstNum   Device instance number to get the information for. Used
 *                       when multiple devices are present on a board.
 *
 *  \return SoC_Ctrl_Mod_ID        If found, returns the SoC module ID which is
 *                                 used for controlling this device.
 *  \return INVALID_MOD_ID         If device is not found, returns invalid
 *                                 module ID.
 */
uint32_t BOARDGetDeviceCtrlModId(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Returns the instance number of the SoC module to which the device is
 *          connected for controlling it. Usually, this will be the instance
 *          number of I2C, SPI or GPIO on the SoC.
 *
 *  \param  devId        Device ID to get the information for.
 *  \param  devInstNum   Device instance number to get the information for. Used
 *                       when multiple devices are present on a board.
 *
 *  \return Ctrl_mod_inst_num       If device is found, returns the instance
 *                                  number of the SoC module to which the device
 *                                  is connected for controlling it.
 *  \return BOARD_INVALID_INST_NUM  If device is not found.
 */
uint32_t BOARDGetDeviceCtrlModInstNum(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Returns the connection information between the SoC module used for
 *          controlling the device, and the device. For example:
 *          - For I2C, it is the I2C slave address.
 *          - For SPI, it is the Chip Select.
 *          - For GPIO, it is the GPIO pin number.
 *
 *  \param  devId        Device ID to get the information for.
 *  \param  devInstNum   Device instance number to get the information for. Used
 *                       when multiple devices are present on a board.
 *
 *  \return Control_information         If device is found
 *  \return BOARD_INVALID_INFO          If device is not found. BOARD_INVALID_INFO is
 *                                      also returned if no relevant info is
 *                                      present, as may be the case if the
 *                                      module does not require any additional
 *                                      information for controlling the device.
 */
uint32_t BOARDGetDeviceCtrlInfo(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Returns the ID of the SoC peripheral the device has a data
 *          connection to. For example, McASP sends data to the codec device.
 *          In that case, the dataModId would be set to the ID for McASP.
 *
 *  \param  devId        Device ID to get the information for.
 *  \param  devInstNum   Device instance number to get the information for. Used
 *                       when multiple devices are present on a board.
 *
 *  \return SoC_Data_Mod_ID        If found, returns the SoC module ID which is
 *                                 used for data transfer to/from this device.
 *  \return INVALID_MOD_ID        If device is not found, returns invalid
 *                                 module ID.
 */
uint32_t BOARDGetDeviceDataModId(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Returns the instance number of the SoC module the device has a data
 *          connection to. For example, McASP sends data to the codec device.
 *          In that case, the instance number of the McASP would be returned as
 *          the dataModInstNum for that device.
 *
 *  \param  devId        Device ID to get the information for.
 *  \param  devInstNum   Device instance number to get the information for. Used
 *                       when multiple devices are present on a board.
 *
 *  \return Data_mod_inst_num       If device is found, returns the instance
 *                                  number of the SoC module that has a data
 *                                  connection to this device.
 *  \return BOARD_INVALID_INST_NUM  If device is not found, or if no
 *                                  relevant information is present.
 */
uint32_t BOARDGetDeviceDataModInstNum(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Perform Power On for the provided device through GPIO or I2C IO
 *          expander. If Power On is not needed this function returns success
 *          without reporting error.
 *
 *  \param  devId        Device ID to power-on.
 *  \param  devInstNum   Device instance number. Used when multiple devices are
 *                       present in a board.
 *  \param  powerOn      TRUE - power on, FALSE - power down
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t BOARDPowerOnDevice(uint32_t devId,
                           uint32_t devInstNum,
                           uint32_t powerOn);

/**
 *  \brief  Enable board level mux for the provided device.
 *          If no muxing is needed, this function returns success without
 *          reporting error.
 *
 *  \param  devId        Device ID to select.
 *  \param  devInstNum   Device instance number. Used when multiple devices are
 *                       present in a board.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t BOARDSelectDevice(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief  Perform reset for the provided device through GPIO or I2C IO
 *          expander. If reset is not needed this function returns success
 *          without reporting error.
 *
 *  \param  devId        Device ID to reset.
 *  \param  devInstNum   Device instance number. Used when multiple devices are
 *                       present in a board.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t BOARDResetDevice(uint32_t devId, uint32_t devInstNum);

/**
 *  \brief Sets particular mode specific to the device.
 *
 *  Note: This API should be called only after calling power on and select
 *  device functions as calling the device select function after this could
 *  set the mode to default.
 *
 *  \param devId        [IN] Device ID to set the mode.
 *  \param instId       [IN] Instance ID. Used when multiple devices are
 *                           present in a board.
 *  \param boardMod    [IN] Mode param.
 *
 *  \return STW_SOK on success, else appropriate error code on failure.
 *          Note: This function returns STW_SOK even if no mux programming
 *                is required for a particular mode of operation.
 */
int32_t BOARDSelectMode(uint32_t    devId,
                        uint32_t    instId,
                        boardMode_t boardMod);

/**
 *  \brief  Funtion to print all the board information like board type,
 *          board revision etc...
 */
void BOARDPrintInfo(void);

/**
 *  \brief  Checks if the specified device is present on the board.
 *
 *  \param  devId        Device ID to get the information for.
 *
 *  \return TRUE                   If device is present on the board
 *  \return FALSE                  If device is not present on the board
 */
uint32_t BOARDIsDevicePresent(uint32_t devId);

/**
 *  \brief  Returns the number of instances of the specified device present on
 *          the board.
 *
 *  \param  devId        Device ID to get the information for.
 *
 *  \return numDevFound  If device is present on the board, returns the number
 *                       of instances of the device on the board.
 *  \return 0            If device is not present on the board
 */
uint32_t BOARDGetNumDevices(uint32_t devId);

/**
 * \brief   Configures IO pins needed by for module. This API uses the pin mux
 *          data and configures the pinmux of requested module and instance.
 *
 * \param   moduleId    Module ID of the peripheral
 * \param   instNum     Instance number of the module
 * \param   boardMod   Mode param
 *
 **/
void BOARDConfigModulePinMux(uint32_t moduleId,
                             uint32_t instNum,
                             uint32_t boardMod);

/**
 *  \brief Returns the device instance to which the video device is connected
 *  corresponding capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return Device instance if found else returns BSP_BOARD_INVALID_INST_ID.
 */
uint32_t BOARDGetVideoDeviceInstId(uint32_t devDrvId,
                                   uint32_t drvId,
                                   uint32_t drvInstId);

/**
 *  \brief Returns the I2C instance to which the video device is connected
 *  corresponding capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return I2C instance if found else returns HSI2C_INST_MAX.
 */
uint32_t BOARDGetVideoDeviceI2cInstId(uint32_t devDrvId,
                                      uint32_t drvId,
                                      uint32_t drvInstId);

/**
 *  \brief Returns the video device I2C address connected to the corresponding
 *  capture/display driver and instance.
 *
 *  \param devDrvId     [IN] Video device driver ID to get the info for.
 *  \param drvId        [IN] Driver ID to which the device is connected.
 *  \param drvInstId    [IN] Driver instance to which the device is connected.
 *
 *  \return I2C address of the device if found else returns 0.
 */
uint32_t BOARDGetVideoDeviceI2cAddr(uint32_t devDrvId,
                                    uint32_t drvId,
                                    uint32_t drvInstId);

/**
 *  \brief Returns the console Instance ID of the connected Board
 *
 *
 *  \return console Instance ID
 */
uint32_t BOARDGetConsoleInstID(void);

/**
 * \brief   Configures IO pins needed by UART console. This API uses the pin mux
 *          data and configures the pinmux of UART console for default mode
 *
 * \param   uartInstId     Instance number of the UART console
 *
 **/
void BOARDConfigConsolePinMux(uint32_t uartInstId);

/**
 *  \brief BOARDInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #boardInitParams_t structure.
 *
 */
static inline void BoardInitParams_init(boardInitParams_t *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BoardInitParams_init(boardInitParams_t *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->boardId               = BOARD_MAX;
        initPrms->baseBoardRev          = BOARD_REV_MAX;
        initPrms->dcBoardRev            = BOARD_REV_MAX;
        initPrms->customData            = NULL;
        initPrms->isDefPinMuxSettingReq = (uint32_t) TRUE;
    }

    return;
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif /* ifdef __cplusplus */

#endif /* #ifndef STW_BOARD_H_ */
