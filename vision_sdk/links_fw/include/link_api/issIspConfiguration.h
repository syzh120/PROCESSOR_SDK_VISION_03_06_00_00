/*
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
*/

/**
 *******************************************************************************
 *   \addtogroup ISSM2MISP_LINK_API
 *
 *   This file defines structure for ISS ISP configuration.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file issIspConfiguration.h
 *
 * \brief ISS Isp Configuration structure definition file
 *
 * \version 0.0 (Jun 2014) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ISSISPCONFIG_H_
#define ISSISPCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>
#include <ti/drv/vps/include/iss/vps_cfgcnf.h>
#include <ti/drv/vps/include/iss/vps_cfgglbce.h>
#include <ti/drv/vps/include/iss/vps_cfgh3a.h>
#include <ti/drv/vps/include/iss/vps_cfgipipe.h>
#include <ti/drv/vps/include/iss/vps_cfgipipeif.h>
#include <ti/drv/vps/include/iss/vps_cfgisif.h>
#include <ti/drv/vps/include/iss/vps_cfgisp.h>
#include <ti/drv/vps/include/iss/vps_cfgldc.h>
#include <ti/drv/vps/include/iss/vps_cfgnsf3.h>
#include <ti/drv/vps/include/iss/vps_cfgrsz.h>
#include <ti/drv/vps/include/iss/vps_cfgsimcop.h>
#include <ti/drv/vps/include/iss/vps_cfgvtnf.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief IPIPE 3D Lut table Format
 *
 * There are two formats supported by the 3D Lut table, ie
 *******************************************************************************
*/
typedef enum
{
    ISS_ISP_IPIPE_3D_LUT_FORMAT_RGB = 0,
    /**< Lut contains RGB table for 3D,
         this table format is not directly supported by the IP, so it
         requires conversion, ISP link does this conversion. */
    ISS_ISP_IPIPE_3D_LUT_FORMAT_BANK = 1,
    /**< Lut contains table of four arrays for each bank,
         this table format is supported by the IP */
    ISS_ISP_IPIPE_3_DLUT_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} IssIspIpipe3dLutFormat_t;


/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 * \brief Advanced parameters for re-sizer operation
 *
 *  These are advanced parameters for re-sizer operation. In create params init
 *  default values for these will be configured. If application is interested,
 *  then after init, values for these can be altered.
 *******************************************************************************
*/
typedef struct
{
    vpsissRszFlipCtrl_t flipCtrl;
    /**< Used to flip the output in horizontal and/or vertical direction */

    vpsissRszScaleMode_t scaleMode;
    /**< Rescaled Mode, could be either Normal or Downscale mode */

    vpsissRszFiltConfig_t filtCfg;
    /**< Structure containing Filter configuration for luma and chroma on
         horizontal and vertical side */

    vpsissRszIntsConfig_t intensityCfg;
    /**< Structure containing intensity configuration for luma and chroma on
         horizontal and vertical side */

    UInt32 alpha;
    /**< 8 Bit Alpha value (8-bits lsb is valid), in the case of
     *    SYSTEM_DF_ARGB32_8888 data format. For other formats, this parameter
     *    is don't care.
     */

} IssIspRszParams;

/**
 *******************************************************************************
 * \brief ISS ISP Configuration Parameters
 *******************************************************************************
*/
typedef struct
{
    UInt32 channelId;
    /**< Channel Id to which this configuration needs to be applied */

    /**< If the pointer is NULL: Indicates application is not interested in configuring values.
     *   If the pointer is non-NULL:  Indicates application is providing values to configure them.
     *   Note that, the structure (Memory) area pointed to these buffers are available for the link
     *   and they are not over-written, while the link is active.
     */
    vpsissCnfConfig_t             *cnfCfg;

    vpsissGlbceConfig_t           *glbceCfg;
    vpsissGlbcePerceptConfig_t    *glbceFwdPerCfg;
    vpsissGlbcePerceptConfig_t    *glbceRevPerCfg;
    vpsissGlbceWdrConfig_t        *glbceWdrCfg;

    vpsissH3aAewbConfig_t         *aewbCfg;
    vpsissH3aAfConfig_t           *afCfg;

    vpsissIpipeInConfig_t         *ipipeInputCfg;
    vpsissIpipeYuvPhsConfig_t     *yuvPhsCfg;
    vpsissIpipeRgb2RgbConfig_t    *rgb2rgb1Cfg;
    vpsissIpipeRgb2RgbConfig_t    *rgb2rgb2Cfg;
    vpsissIpipeRgb2YuvConfig_t    *rgb2yuvCfg;
    vpsissIpipeWbConfig_t         *wbCfg;
    vpsissIpipeCfaConfig_t        *cfaCfg;
    vpsissIpipeDpcOtfConfig_t     *dpcOtfCfg;
    vpsissIpipeDpcLutConfig_t     *dpcLutCfg;
    vpsissIpipeGammaConfig_t      *gammaCfg;
    vpsissIpipe3DLutConfig_t      *lut3d;
    IssIspIpipe3dLutFormat_t       ipipe3dLutFormat;
    vpsissIpipeEeConfig_t         *eeCfg;
    vpsissIpipeGicConfig_t        *gicCfg;
    vpsissIpipeLscConfig_t        *lscCfg;
    vpsissIpipeNf2Config_t        *nf1Cfg;
    vpsissIpipeNf2Config_t        *nf2Cfg;

    vpsissIpipeifLutConfig_t      *ipipeifLut;
    vpsissIpipeifWdrCfg_t         *ipipeifWdrCfg;
    vpsissIpipeifDeCompandInsts_t *ipipeifCmpDecmpCfg;

    vpsissIsifGainOfstConfig_t    *isifWbCfg;
    vpsissIsifBlackClampConfig_t  *isifBlkClampCfg;
    vpsissIsif2DLscConfig_t       *isif2DLscCfg;

    vpsissNsf3Config_t            *nsf3vCfg;

} IssIspConfigurationParameters;

/*******************************************************************************
 *  \brief Structure of AEWB output parameters
 *******************************************************************************
 */
typedef struct {
    UInt32 channelId;
    /**< Channel Id for which this output params are valid */

    struct {
        UInt32 useAeCfg;
        /**< Flag to indicate whether to use exposureTime, analogGain
             and digital Gains or not */
        UInt32 exposureTime;
        /**< Exposure Time in micro seconds */
        UInt32 analogGain;
        /**< Analog Gains,
             Step size is same as Sensor gain step size */
        UInt32 digitalGain;
        /**< Digital Gains,
             Step size is same IPIPE gain step size */

        UInt32 useWbCfg;
        /**< Flag to indicate whether to use White balance gains or not */
        UInt32 gain[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */
        UInt32 offset[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */

        UInt32 useColorTemp;
        /* Flag to indicate whether to use color temp or not */
        UInt32 colorTemparature;
        /**< Color Temperature */
    } outPrms[2U];
    /**< For 2 PASS WDR. Currently applying for only 1 PASS */

    IssIspConfigurationParameters ispCfg;
    /**< ISP parameters from AEWB output */

    UInt32 numParams;
    /**< Number of valid entries in outPrms */

    UInt32 exposureRatio;
    /**< Exposure Ratio,
         Read from the sensor when Wdr mode is enabled
         ISP Merge parameters are calculated based on this ratio */
} IssAewbAlgOutParams;

typedef struct {
    UInt16 subSampleAcc[4U];
    UInt16 saturatorAcc[4U];
} IssAwebH3aOutSumModeOverlay;

typedef struct {
    UInt16 unsatCount[8U];
} IssAwebH3aOutUnsatBlkCntOverlay;

typedef struct {
    UInt32 hfvSum_0;
    UInt32 hfv1_0;
    UInt32 hfv2_0;
    UInt32 reserved_0;

    UInt32 hfvSum_1;
    UInt32 hfv1_1;
    UInt32 hfv2_1;
    UInt32 reserved_1;

    UInt32 hfvSum_2;
    UInt32 hfv1_2;
    UInt32 hfv2_2;
    UInt32 reserved_2;
} IssAfH3aOutHfModeOverlay;

typedef struct {

    UInt32 hfvSum;
    UInt32 hfv1;
    UInt32 hfv1Square;
    UInt32 hfv1Count;

    UInt32 hfv2;
    UInt32 hfv2Square;
    UInt32 hfv2Count;
    UInt32 reserved_0;

    UInt32 vfv1;
    UInt32 vfv1Square;
    UInt32 vfv1Count;
    UInt32 reserved_1;

    UInt32 vfv2;
    UInt32 vfv2Square;
    UInt32 vfv2Count;
    UInt32 reserved_2;

} IssAfH3aOutHfVfModeOverlay;

typedef union {
    IssAfH3aOutHfModeOverlay hfOut;
    IssAfH3aOutHfVfModeOverlay hvVfOut;
} IssAfH3aOutOverlay;

/**
 *******************************************************************************
 *
 * \brief Set defaults for ISP config params
 *
 *  Currently, it resets config parameters to 0
 *
 * \param  pPrm [OUT] ISP Configuration Parameters.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssM2mIspLink_ConfigParams_Init(
    IssIspConfigurationParameters *pPrm);


/**
 *******************************************************************************
 *
 * \brief Set defaults for ISP config params
 *
 *  Currently, it resets config parameters to 0
 *
 * \param  pPrm [OUT] ISP Configuration Parameters.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssM2mIspLink_ConfigParams_Init(
    IssIspConfigurationParameters *pPrm)
{
    memset(pPrm, 0, sizeof(IssIspConfigurationParameters));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
