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
********************************************************************************
 * @file  idcc.c
 *
 * @brief DCC Interface, contains defination of structures and functions,
 *        which are called by algo plugin layer
 *
********************************************************************************
*/
#ifndef _I_DCC_
#define _I_DCC_

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/

/* DCC is dependent on the ISS header files */

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

#include <TI_aaa_awb.h>

/*---------------------- data declarations -----------------------------------*/

#define DCC_RGB2RGB1_MAX_PHOTO_SPACE_INST       (10U)
#define DCC_RGB2RGB2_MAX_PHOTO_SPACE_INST       (10U)
#define DCC_3D_LUT_MAX_PHOTO_SPACE_INST         (10U)
#define DCC_NSF3V_MAX_PHOTO_SPACE_INST          (10U)
#define DCC_CNF_MAX_PHOTO_SPACE_INST            (10U)

/* This should be the max of all photospace instance */
#define DCC_MAX_PHOTO_SPACE_INST                (10U)

/* Mesh LDC Table Size, allocated at create time.
   Current implementation supports 1080p frame down scaled by 16
   in both direction */
#define DCC_MESH_LDC_TABLE_SIZE                 ((1920/16 + 1) *               \
                                                 (1080/16 + 1) * 2 * 2)

/* ISIF 2D LSC gain and offset table size, allocated at create time.
   Current implementation supports 1080p frame down scaled by 8
   in both direction */
#define DCC_ISIF_2D_LSC_GAIN_TABLE_SIZE         ((1920/8 + 1) *                \
                                                 (1080/8 + 1) * 4)

typedef enum
{
    DCC_PHOTOSPACE_AG = 0,
    /* Analog Gain */
    DCC_PHOTOSPACE_ET,
    /* Exposure Time */
    DCC_PHOTOSPACE_CT,
    /* Color Temparature */
    DCC_MAX_PHOTO_SPACE
} dcc_photospace_dim_id;

/**
 *******************************************************************************
 *  @struct dcc_parser_input_params_t
 *  @brief  This structure contains input parameters
 *
 *  @param  dcc_buf           : pointer to the buffer where dcc profile
                                are stored
 *  @param  dcc_buf_size      : Size of the dcc profile buffer
 *  @param  color_temparature : Color temperature of the scene
 *  @param  exposure_time     : exposure time use gad for the current scene
 *  @param  analog_gain       : analog gain used used in the current scene
 *
 *******************************************************************************
*/
typedef struct
{
    UInt8  *dcc_buf;
    UInt32 dcc_buf_size;
    UInt32 color_temparature;
    UInt32 exposure_time;
    UInt32 analog_gain;
    UInt32 cameraId;
} dcc_parser_input_params_t;

typedef struct
{
    UInt32 min;
    UInt32 max;
} dcc_parser_dim_range;


/**
 *******************************************************************************
 *  @struct dcc_parser_input_params_t
 *  @brief  This structure contains output parameters
 *
 *  @param  iss_drv_config           : Pointer to iss drivers config
 *  @param  dcc_buf_size      : Size of the dcc profile buffer
 *  @param  color_temparature : Color temperature of the scene
 *  @param  exposure_time     : exposure time use gad for the current scene
 *  @param  analog_gain       : analog gain used used in the current scene
 *
 *******************************************************************************
*/
typedef struct {

    UInt32                      useDpcOtfCfg;
    vpsissIpipeDpcOtfConfig_t   ipipeDpcOtfCfg;

    UInt32                      useNf1Cfg;
    vpsissIpipeNf2Config_t      ipipeNf1Cfg;

    UInt32                      useNf2Cfg;
    vpsissIpipeNf2Config_t      ipipeNf2Cfg;

    UInt32                      useCfaCfg;
    vpsissIpipeCfaConfig_t      ipipeCfaCfg;

    UInt32                      useGicCfg;
    vpsissIpipeGicConfig_t      ipipeGicCfg;

    UInt32                      useGammaCfg;
    vpsissIpipeGammaConfig_t    ipipeGammaCfg;
    UInt32                      gammaLut[1024U];

    UInt32                      useRgb2YuvCfg;
    vpsissIpipeRgb2YuvConfig_t  ipipeRgb2YuvCfg;

    UInt32                      useYeeCfg;
    vpsissIpipeEeConfig_t       ipipeYeeCfg;
    UInt32                      yeeLut[1024U];

    UInt32                      useBlackClampCfg;
    vpsissIsifBlackClampConfig_t blkClampCfg;

    UInt32                      useAwbCalbCfg;
    awb_calc_data_t             awbCalbData;

    UInt32                      useIpipeifVpDeComp;
    UInt32                      ipipeifVpDecompLut[513U];

    UInt32                      useIpipeifWdrCompCfg;
    UInt32                      ipipeifWdrCompLut[513U];

    vpsissIpipeifDeCompandInsts_t ipipeifCmpDecmpCfg;

    UInt32                      useIpipeifWdrCfg;
    vpsissIpipeifWdrCfg_t       ipipeifWdrCfg;

    vpsissIpipeifLutConfig_t    ipipeifLutCfg;

    /* Mudules supporting multiple photospace */
    UInt32                      useRgb2Rgb1Cfg;
    dcc_parser_dim_range        phPrmsRgb2Rgb1
                                    [DCC_RGB2RGB1_MAX_PHOTO_SPACE_INST]
                                    [DCC_MAX_PHOTO_SPACE];
    UInt32                      ipipeNumRgb2Rgb1Inst;
    vpsissIpipeRgb2RgbConfig_t *ipipeRgb2Rgb1Cfg;

    UInt32                      useRgb2Rgb2Cfg;
    dcc_parser_dim_range        phPrmsRgb2Rgb2
                                    [DCC_RGB2RGB2_MAX_PHOTO_SPACE_INST]
                                    [DCC_MAX_PHOTO_SPACE];
    UInt32                      ipipeNumRgb2Rgb2Inst;
    vpsissIpipeRgb2RgbConfig_t *ipipeRgb2Rgb2Cfg;

    UInt32                      useNsf3vCfg;
    dcc_parser_dim_range        phPrmsNsf3v
                                    [DCC_NSF3V_MAX_PHOTO_SPACE_INST]
                                    [DCC_MAX_PHOTO_SPACE];
    UInt32                      numNsf3vInst;
    vpsissNsf3Config_t         *nsf3vCfg;

    UInt32                      useCnfCfg;
    dcc_parser_dim_range        phPrmsCnf
                                    [DCC_CNF_MAX_PHOTO_SPACE_INST]
                                    [DCC_MAX_PHOTO_SPACE];
    UInt32                      numCnfInst;
    vpsissCnfConfig_t          *cnfCfg;

    UInt32                      use3dLutCfg;
    dcc_parser_dim_range        phPrms3dLut
                                    [DCC_3D_LUT_MAX_PHOTO_SPACE_INST]
                                    [DCC_MAX_PHOTO_SPACE];
    UInt32                      num3dLutInst;
    vpsissIpipe3DLutConfig_t   *ipipe3dLutCfg;
    UInt16                      lut3D[3][729];

    UInt32                      useGlbceCfg;
    vpsissGlbceConfig_t         glbceCfg;
    UInt32                      useGlbceFwdPerCfg;
    vpsissGlbcePerceptConfig_t  glbceFwdPerCfg;
    UInt32                      useGlbceRevPerCfg;
    vpsissGlbceConfig_t         glbceRevPerCfg;
    UInt32                      useGlbceWdrCfg;
    vpsissGlbceConfig_t         glbceWdrCfg;

    UInt32                      useAewbCfg;
    vpsissH3aAewbConfig_t       aewbCfg;

    UInt32                      useMeshLdcCfg;
    vpsissldcConfig_t           ldcCfg;
    UInt8                      *ldcTable;

    UInt32                      useIsif2DLscCfg;
    vpsissIsif2DLscConfig_t     isif2DLscCfg;
    UInt8                      *isif2DLscGainTbl;
    UInt8                      *isif2DLscOffsetTbl;
} dcc_parser_output_params_t;

#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
*                         FUNCTION DEFINITIONS
*******************************************************************************/

/**
********************************************************************************
 * @fn      dcc_update(dcc_parser_input_params_t * input_params,
 *                     iss_drv_config_t *iss_drv_config
 *                    )
 *
 * @brief   This function identfies the dcc profile from input params structure
 *          and updates the iss driver configuration
 *          In the current implementation, it parses input bit file to
 *          get the ISP configuration and returns isp configuration
 *          in the output parameters
 *
 * @param   input_params
 *          input parameters for the dcc parser
 *
 *
 * @return  int
 *          sucess/failure
********************************************************************************
*/

int dcc_update(dcc_parser_input_params_t * input_params,
               dcc_parser_output_params_t *output_params);

#ifdef __cplusplus
}
#endif

#endif
