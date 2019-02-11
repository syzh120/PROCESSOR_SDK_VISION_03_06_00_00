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

/*
 *******************************************************************************
 *
 * \file iss_utils.h
 *
 * \brief This file contains utility functions for initializing ISS
 *        data structures.
 *
 *******************************************************************************
 */


#ifndef ISS_UTILS_H_
#define ISS_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <include/link_api/issIspConfiguration.h>
#include <include/link_api/issSimcopConfiguration.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>
#include "app_util_iss.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/*
sensorDrvId is not used in sensor driver
Therefore it is OK to define it as 0
*/
#define FVID2_VID_SENSOR_MARS_APT_AR0233_DRV 0



/*******************************************************************************
 *  Structure declaration
 *******************************************************************************
 */

/*  \brief Structure used for describing sensor interfacing.
 *         Initialized in the platform file
 */
typedef struct
{
    UInt32                              i2cInstId;
    /**< I2C Instance id for the sensor */
    UInt8                               i2cAddr[ISSCAPT_LINK_MAX_CH];
    /**< I2C Address of the sensor */
    UInt8                               i2cAddrSer[ISSCAPT_LINK_MAX_CH];
    /**< I2C Address of the serializer */
    Bool                                isMultiChannel;
    /**< Flag for single/multi channel sensor config */
    System_VideoIfWidth                 videoIfWidth;
    /**< Interface width */
    System_VideoIfMode                  videoIfMode;
    /**< Interface mode */
    System_Csi2DataFormat               inCsi2DataFormat;
    /**< Input CSI2 Data Format, valid only if videoIfMode is CSI2 */
    UInt32                              inCsi2VirtualChanNum;
    /**< CSI2 Virtual Channel Num, must be between 0 to 3 */
    Bool                                isEnableCSIPostConfig;
    /**< Enable to enable CSI output in UB960 */
    IssCaptureLink_Csi2Params           csi2Prms[ISSCAPT_LINK_MAX_CMPLXIO_INST];
    /**< CSI2 Params when sensor is CSI2 based */
    UInt32                              sensorDrvId;
    /**< Sensor Driver Id */
    Bool                                sensorBroadcast;
    /**< Enable/Disable sensor broadcast */
    Bool                                enableFsin;
    /**< Enable/Disable sensor Frame Sync Input (FSIN) */
    UInt8                               deserializerAddr[2];
} ChainsCommon_IssSensorIf;

#define DEV_MAX_NAME_LEN                    (50U)

/**
 *  \brief FPD LInk camera configuration parameter structure.
 */

typedef struct
{
    char name[DEV_MAX_NAME_LEN];
    /**< device name */
    BspUtils_Ub960I2cParams    * desCfgScript;
    /**< Deserializer Configuration Script */
    UInt16                             num_des_registers;
    /**< Deserializer Configuration Script Length*/
    BspUtils_Ub960I2cParams    * serCfgScript;
    /**< Serializer Configuration Script */
    UInt16                             num_ser_registers;
    /**< Serializer Configuration Script Length*/
    BspUtils_FpdCamPowerLevel    cam_pwr_level;
    /**< Camera Power Level */
    UInt32    waitAfterPowerOn;
    /**< ms to wait after device Power ON */
    UInt8    broadCastEnable;
    /**< ms to wait after device Power ON */
}IssUtils_Ub96xSerDesCfg;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */
/*  \brief Function to initialize ISP modules create parameters for
 *         the given sensor
 *
 *  \params name             [IN]  Name of the sensor
 *  \params pCapturePrms     [OUT] Pointer to ISS Capture create Parameters
 *  \params pIspPrms         [OUT[ Pointer to ISP create parameters
 *  \params pSimcopPrms      [OUT[ Pointer to Simcop create parameters
 *  \params ispOpMode        [IN]  ISP Operating mode
 *  \params simcopOpMode     [IN]  Simcop Operating mode
 *  \returns none.
 */
Void IssUtils_SetCreateParams(char name[],
        IssCaptureLink_CreateParams *pCapturePrm,
        IssM2mIspLink_CreateParams *pIspPrm,
        IssM2mSimcopLink_CreateParams *pSimcopPrm,
        IssM2mIspLink_OperatingMode ispOpMode,
        IssM2mSimcopLink_OperatingMode simcopOpMode);

/*  \brief Function to set LDC/VTNF config based on the bypass flags
 *         This funciton is used at runtime from the usecase to
 *         enable/disable LDC/VTNF.
 *
 *  \params ldcCfg           [OUT] Pointer to LDC configuration
 *  \params vtnfCfg          [OUT] Pointer to VTNF configuration
 *  \params bypassVtnf       [IN]  Flag to indicate whether to bypas VTNF
 *  \params bypassLDC        [IN]  Flag to indicate whether to bypas LDC
 *  \returns none.
 */
Void IssUtils_SetimcopLdcVtnfRtConfig(
                        vpsissldcConfig_t *ldcCfg,
                        vpsissvtnfConfig_t *vtnfCfg,
                        Bool bypssVtnf,
                        Bool bypssLdc);

/*  \brief Function to Read and Parse DCC configuraton.
 *         It reads dcc profile from the given qspi offset.
 *         If DCC profile is valid, it parses dcc profile and sets
 *          the configuration in isp/simcop variables
 *         If DCC profile is not valie from qspi, it uses provided
 *          DCC profile from the sensor and parses it./
 *
 *  \params qSpiOffset       [IN]  QSPI offset from where to read DCC Profile
 *  \params pSensorDccCfg    [IN]  Pointer to sensor provided DCC profile,
 *                                 used only if DCC profile from qspi is not valid
 *  \params sensorDccCfgSize [IN]  Size of the sensor provided dcc profile
 *  \params linkId           [IN]  AEWB Link Id, used for getting memory
 *                                  to store dcc profile
 *  \returns none.
 */
Void IssUtils_ReadAndParseDccConfig(
        UInt32 qSpiOffset,
        UInt8 *pSensorDccCfg,
        UInt32 sensorDccSize,
        UInt32 linkId);

/*  \brief Initializes Simcop Configurations to the default values,
 *          Mainly used for initializing LDC configuration
 *
 *  \params vSimcopCfg       [OUT] Pointer to Simcop configuration
 *  \params bypassVtnf       [IN]  Flag to indicate whether to bypas VTNF
 *  \params bypassLDC        [IN]  Flag to indicate whether to bypas LDC
 *
 *  \returns none.
 */
Void IssUtils_InitSimcopConfig(
        IssM2mSimcopLink_ConfigParams *pSimcopCfg,
        Bool bypassLdc,
        Bool bypassVtnf);
Void IssUtils_InitConfig(
        IssIspConfigurationParameters *pIspCfg,
        IssM2mSimcopLink_ConfigParams *pSimcopCfg,
        Bool bypassLdc,
        Bool bypassVtnf);


/*  \brief Function to enables detection of CRC error on CSI2 interface
 *
 *  params captSrc      Source from which CAL is used to capture.
 *  params issCaptureLinkId  Capture Link identifier. Required to configure
 *                          the link to detect errors.
 *  returns none.
 */
Void ChainsCommon_SetIssCaptureErrorHandlingCb(UInt32 issCaptureLinkId);

/*  \brief Function to get sensor interfacing information
 *
 *  params info      Output sensor interface structure, in which interface
 *                   informance will be returned.
 *                   Must be implemented by platform file.
 *  returns none.
 */
Int32 ChainsPlatform_GetSensorIntfInfo(char name[],
    ChainsCommon_IssSensorIf *info);

/*  \brief Function to get Serializer/Deserializer config for the given sensor.
 *
 *  params info  Serializer Config Script, Deserializer Config Script
 *                   Power Level, Wait Period.
 *                   Must be implemented by platform file.
 *  returns none.
 */

Int32 ChainsPlatform_GetSensorSerDesCfg(char name[],
    IssUtils_Ub96xSerDesCfg* cfg);


Void ChainsPlatform_SetPinMux(char name[]);

/*  \brief Function to set Board Mux
 *
 *  params name      Name of the sensor, as defined in iss_sensors.h file.
 *                   Must be implemented by board file.
 *  returns none.
 */
Void ChainsBoard_SetBoardMux(char name[]);

Void IssUtils_CopySensorName(char name[]);

Int32 IssUtils_appInitUb960(UInt32 instId,
                            UInt32 sensorDrvId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            IssUtils_Ub96xSerDesCfg * devSerDesCfg,
                            Bool sensorBroadcast,
                            BspUtils_Ub960Status *pStatus);
Int32 IssUtils_updateSlaveAddrUb960(UInt32 instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr);
Int32 IssUtils_appUb960EnableFsin(UInt32 instId,
                            UInt32 sensorDrvId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            const BspUtils_Ub960Status *pStatus);
Int32 IssUtils_getDebugRegVal(UInt32 instId,
                                  UInt32 sensorDrvId,
                                  const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                                  BspUtils_Ub960DebugRegData *pDebugStatus);
static Int32 initDeserializer(UInt32 instId);

#ifdef BOARD_TYPE_TDA3XX_RVP
static Int32 resetDeserializer(void);
static Int32 writeI2Cconfig(Int32 regCount, BspUtils_Ub960I2cParams *params, UInt32 slaveAddr);
#endif


static Int32 configDeserializer(UInt32 instId, BspUtils_Ub960I2cParams * desCfgScript, UInt16 numDesRegs, Bool sensorBroadcast);
static Int32 configSerializer(UInt32 i2cDevAddr, BspUtils_Ub960I2cParams* serCfgScript, UInt16 numSerRegs);
static Int32 setCameraPower(BspUtils_FpdCamPowerLevel pwrlvl);
static Int32 IssUtils_appInitUB913PassThroughGPIO0(UInt32 instId, UInt32 portId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* end of ISS_UTILS_H_ */

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
