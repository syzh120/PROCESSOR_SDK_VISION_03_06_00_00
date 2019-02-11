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
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_CHAINS_ISS_API APIs for controlling ISS sensors
 *
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file iss_sensors_if.h
 *
 * \brief APIs for controlling external sensors.
 *
 *
 *******************************************************************************
 */

#ifndef ISS_SENSORS_IF_H_
#define ISS_SENSORS_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/* Including system.h for Int32/UInt32 data type */
#include <include/link_api/system.h>

#include <iss_sensors.h>
/* Sensor Layer provides ISP configuration for few ISP modules,
   Once this ISP modules are supported in the DCC, this header file and
   getIspConfig will be removed from the sensor layer */
#include <include/link_api/issIspConfiguration.h>
/* Sensor layer provides AEWB configuration for each sensor,
   It should be moved to ISS utils.
   Once moved, this file and initAewbConfig callback will be removed
   from the sensor framework */
#include <algorithmLink_issAewb.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/* Forward Declaration of Sensor Params */
typedef struct IssSensorIf_Params_t IssSensorIf_Params;

typedef Int32 (*IssSensorIf_Start) (UInt32 chId,
    IssSensor_CreateParams *pCreatePrms);
typedef Int32 (*IssSensorIf_Stop) (UInt32 chId,
    IssSensor_CreateParams *pCreatePrms);
typedef Int32 (*IssSensorIf_SetAeParams) (
    IssSensor_CreateParams *pCreatePrms, IssSensor_AeParams *pAePrms);
typedef Int32 (*IssSensorIf_GetDccParams) (
    IssSensor_CreateParams *pCreatePrms, IssSensor_DccParams *pDccPrms);
typedef Int32 (*IssSensorIf_GetExpParams) (
    IssSensor_CreateParams *pCreatePrms, IssSensor_ExposureParams *pExpPrms);
typedef Void (*IssSensor_InitAewbConfig) (
    IssSensor_CreateParams *pCreatePrms,
    AlgorithmLink_IssAewbCreateParams *pAewbPrms);
typedef Void (*IssSensor_GetIspConfig) (
    IssSensor_CreateParams *pCreatePrms,
    IssIspConfigurationParameters *pIspCfg);
typedef Int32 (*IssSensor_ReadWriteRegister) (
    IssSensor_CreateParams *pCreatePrms,
    UInt32 readWriteFlag,
    IssSensor_ReadWriteReg *pReg);

/**
 *  \brief Structure containins sensor information, used for
 *         registering it to the sensor framework.
 */
struct IssSensorIf_Params_t {
    char                            name[ISS_SENSORS_MAX_NAME];
    /**< Name of the sensor, using which it is registered to this framework */

    IssSensor_Info                  info;
    /**< Sensor information, which does not change */

    UInt32                          dccId;
    /**< DCC Id of the sensor,
         typically sensor driver provides dcc id, but if sensor driver
         is not opened and it is required to flash dcc profile in qspi,
         this id will be used.
         Note: it should be same as the id in the driver */

    IssSensorIf_Start               start;
    IssSensorIf_Stop                stop;
    IssSensorIf_GetExpParams        getExpParams;
    IssSensorIf_SetAeParams         setAeParams;
    IssSensorIf_GetDccParams        getDccParams;
    IssSensor_InitAewbConfig        initAewbConfig;
    IssSensor_GetIspConfig          getIspConfig;
    IssSensor_ReadWriteRegister     readWriteReg;
};

typedef struct {
    UInt16 regAddr;
    UInt16 regValue;
    UInt16 delay;
} IssSensor_ConfigRegs;

/*******************************************************************************
 *  Functions Declarations
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Initialize ISS Sensor framework,
 *        It initializes iss sensor frame work and also calls init functions of
 *        all the supported sensors, which in turn register itself to this
 *        framework.
 *
 *******************************************************************************
*/
Void IssSensorIf_Init();

/**
 *******************************************************************************
 *
 * \brief Used for registering sensor to the iss sensor framework,
 *
 * \params fvid2Id          FVID2 Driver id of the sensor
 * \params pSensorInfo      Pointer to the sensor information structure
 *
 * \return SOK if sensor is registered successfully
 *         error otherwise
 *
 *******************************************************************************
*/
Int32 IssSensorIf_RegisterSensor(IssSensorIf_Params *pSensorPrms);

/**
 *******************************************************************************
 *
 * \brief Initializes Sensor parmas, used for registering sensor to
 *        the iss sensor layer
 *
 * \params prms             Pointer to the sensor params
 *
 *******************************************************************************
*/
static inline Void IssSensorIf_Params_Init(IssSensorIf_Params *prms);


/*******************************************************************************
 *  Functions Declarations
 *******************************************************************************
 */

static inline Void IssSensorIf_Params_Init(IssSensorIf_Params *prms)
{
    UTILS_assert(NULL != prms);

    memset(prms, 0x0, sizeof(IssSensorIf_Params));
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of ISS_SENSORS_IF_H_*/


/*@}*/
