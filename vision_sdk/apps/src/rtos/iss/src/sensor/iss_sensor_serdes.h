/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

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
 * \file iss_sensors_serdes.h
 *
 * \brief APIs for controlling external sensors.
 *
 *
 *******************************************************************************
 */

#ifndef ISS_SENSORS_SERDES_H_
#define ISS_SENSORS_SERDES_H_

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
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**
 * Specify the address that should be associated with TIDA00262. TIDA00262
 *    consists of 913 serializer and AR0140 sensor. Specify the address for both
 *    Address is in 7bit format.
 */
#define PORT_0_SER_ADDR       (0x74U)
      /**< Serializer address */
#define PORT_0_SENSOR_ADDR    (0x40U)
      /**< Sensor address */
#define PORT_1_SER_ADDR       (0x76U)
      /**< Serializer address */
#define PORT_1_SENSOR_ADDR    (0x42U)
      /**< Sensor address */
#define PORT_2_SER_ADDR       (0x78U)
      /**< Serializer address */
#define PORT_2_SENSOR_ADDR    (0x44U)
      /**< Sensor address */
#define PORT_3_SER_ADDR       (0x7AU)
      /**< Serializer address */
#define PORT_3_SENSOR_ADDR    (0x46U)
      /**< Sensor address */
#define PORT_4_SER_ADDR       (0x7eU)
      /**< Serializer address */
#define PORT_4_SENSOR_ADDR    (0x48U)
      /**< Sensor address */
#define PORT_5_SER_ADDR       (0x7cU)
      /**< Serializer address */
#define PORT_5_SENSOR_ADDR    (0x4aU)
      /**< Sensor address */
#define PORT_6_SER_ADDR       (0x80U)
      /**< Serializer address */
#define PORT_6_SENSOR_ADDR    (0x4cU)
      /**< Sensor address */
#define PORT_7_SER_ADDR       (0x82U)
      /**< Serializer address */
#define PORT_7_SENSOR_ADDR    (0x4eU)
      /**< Sensor address */

/** GPIO Addresses on D3 Radar Interface Board */
#define D3RIB_PORT_0_IOEXP_ADDR    (0x48U)
/**< IO EXP address */
#define D3RIB_PORT_1_IOEXP_ADDR    (0x50U)
/**< IO EXP address */
#define D3RIB_PORT_2_IOEXP_ADDR    (0x52U)
/**< IO EXP address */
#define D3RIB_PORT_3_IOEXP_ADDR    (0x54U)
/**< IO EXP address */


#define AR143_MARS_DES_CFG_SIZE    (56U)
#define AR143_MARS_SER_CFG_SIZE    (4U)

#define IMX390_D3_DES_CFG_SIZE    (153U)
#define IMX390_D3_SER_CFG_SIZE    (9U)
#define IMX390_AWR1243_D3_DES_CFG_SIZE    (50U)

#define OV10640_IMI_DES_CFG_SIZE    (55U)
#define OV10640_IMI_SER_CFG_SIZE    (4U)

#define AR0140_TIDA0262_DES_CFG_SIZE    (52U)
#define AR0140_TIDA0262_SER_CFG_SIZE    (4U)

#define OV2775_TIDA1130_DES_CFG_SIZE    (61U)
#define OV2775_TIDA1130_SER_CFG_SIZE    (6U)

#define AR0233_MARS_DES_CFG_SIZE    (70U)
#define AR0233_MARS_SER_CFG_SIZE    (40U)
extern BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_MARS_AR0143[AR143_MARS_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gUB913MarsAR0143SerCfg[AR143_MARS_SER_CFG_SIZE];

extern BspUtils_Ub960I2cParams gUB960DesCfg_D3IMX390[IMX390_D3_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gAppIssUtilsUB953SerCfg_D3IMX390[IMX390_D3_SER_CFG_SIZE];

extern BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_OV10640_IMI[OV10640_IMI_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gUB913_OV10640_IMI_SerCfg[OV10640_IMI_SER_CFG_SIZE];

extern BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_AR0140_TIDA0262_DesCfg[AR0140_TIDA0262_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gUB913_AR0140_TIDA0262_SerCfg[AR0140_TIDA0262_SER_CFG_SIZE];

extern BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_OV2775_TIDA1130_DesCfg[OV2775_TIDA1130_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gUB953_OV2775_TIDA1130_SerCfg[OV2775_TIDA1130_SER_CFG_SIZE];

extern BspUtils_Ub960I2cParams gUB960DesCfg_D3IMX390_AWR1243[IMX390_AWR1243_D3_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gAppIssUtilsUb960Cfg_MARS_AR0233[AR0233_MARS_DES_CFG_SIZE];
extern BspUtils_Ub960I2cParams gUB953MarsAR0233SerCfg[AR0233_MARS_SER_CFG_SIZE];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of ISS_SENSORS_SERDES_H_*/


/*@}*/
