/*
********************************************************************************
 * DCC API
 *
 * "DCC API" is software module developed for TI's ISS based SOCs.
 * This module provides APIs for programming of ISS hardware accelerators
 * which can be used for Imaging and video applications
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
********************************************************************************
*/
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
