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

#ifndef _chains_vipStereoCameraDisplay_Defines_H_
#define _chains_vipStereoCameraDisplay_Defines_H_

#define ALIGN(a,b) ((((a) + ((1<<(b)) - 1)) >> (b)) <<(b))


/* Set if stereo parameters are read from SD card        */
/* Set to 1 only for Dwarp based stereo usecase on TDA3x */
#define READ_SPARAMS_FROM_SD                                    0

/* The param this command takes is Stereo_ConfigurableCreateParams*/
#define SYSTEM_LINK_CMD_STEREO_SET_PARAM                        (0x7000)
#define DISPARITY_TI_LEFT_TO_RIGHT                              0   // Not in param file
#define DISPARITY_TI_RIGHT_TO_LEFT                              1   // Not in param file

/*
 * The parameters set the initial values of the stereo post-processing algorithm and can be set at runtime using the network control tool
 *with command stereo_set_dynamic_params. Please refer to the VisionSDK_NetworkTools_UserGuide.docx for usage .
 * The effects of the command are instantaneous.
 */
#define POSTPROC_COST_MAX_THRESHOLD                             95
#define POSTPROC_CONF_MIN_THRSESHOLD                            98
#define POSTPROC_TEXTURE_LUMALOTHRESH                           0
#define POSTPROC_TEXTURE_LUMAHITHRESH                           100
#define POSTPROC_TEXTURE_THRESHOLD                              85
#define POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD                    64 // 255
#define POSTPROC_MAX_DISP_DISSIMILARITY                         0
#define POSTPROC_MIN_CONFIDENT_N_SEG                            0

#define POSTPROC_HOLEFILLING_STRENGTH                           0
#define POSTPROC_TEMPORAL_FILTER_NUM_FRAMES                     3
#define POSTPROC_MIN_DISPARITY_DISPLAY                          0
#define POSTPROC_COLORMAP_INDEX                                 0 /* 0: multi-color map, 1: blue tone color map */

#define POSTPROC_NUM_FRAC_BITS                                  4  // Not in param file


#define SOFTISP_CROPPED_INPUT_HEIGHT                            664   // Not in param file
#define SOFTISP_OUTPUT_HEIGHT                                   660   // Not in param file

/* The parameters set the initial values of the stereo census transform and disparity algorithms and can be set at runtime using the network control tool
with command stereo_set_params. The effect of the command will only be applied before a use case is started. Once a use case is started, the effec of the command
will only be applied if the use case is stopped and restarted.
Please refer to the VisionSDK_NetworkTools_UserGuide.docx for usage.
 */
#define NUM_DISPARITIES                                         64 //128
#define DISPARITY_STEP_SIZE                                     2 //
#define DISPARITY_SEARCH_DIR                                    DISPARITY_TI_LEFT_TO_RIGHT
#define DISPARITY_WIN_WIDTH                                     11
#define DISPARITY_WIN_HEIGHT                                    11
#define DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP                      1

#define DISPARITY_INPUT_BIT_DEPTH                               32    // Not in param file

#define CENSUS_WIN_WIDTH                                        9
#define CENSUS_WIN_HEIGHT                                       9
#define CENSUS_WIN_HORZ_STEP                                    2
#define CENSUS_WIN_VERT_STEP                                    2

#define CENSUS_INPUT_BIT_DEPTH                                  8     // Not in param file


#define CAPTURE_SENSOR_WIDTH                                    1280
#define CAPTURE_SENSOR_HEIGHT                                   720

#define DISPARITY_OUTPUT_ROI_WIDTH                              640
#define DISPARITY_OUTPUT_ROI_HEIGHT                             360

#define REMAP_OUTPUT_BLOCK_WIDTH                                128 // 16 //128
#define REMAP_OUTPUT_BLOCK_HEIGHT                               16 //8


#define STEREO_CALIB_LUT_SIZE                                   (3*1024U*1024U)
#define STEREO_CALIB_LUT_QSPI_OFFSET                            (29U*1024U*1024U)
#define STEREO_CALIB_LUT_HEADER_SIZE                            (16U)
#define STEREO_CALIB_LUT_TAG_ID                                 (0x00CCAABBU)


/*
 * Camera parameters to generate PCL
 */
// TDA2x
/*
#define BASELINE_FIXED 12.7
#if 0
#define SCALE_FACTOR_X_FIXED 1.6666   // depends on Remap size
#define SCALE_FACTOR_Y_FIXED 1.8750
#define DIST_CENTER_X_FIXED  384.0
#define DIST_CENTER_Y_FIXED  192.0
#else
#define SCALE_FACTOR_X_FIXED 2.8571   // depends on Remap size
#define SCALE_FACTOR_Y_FIXED 2.7273
#define DIST_CENTER_X_FIXED  224.0
#define DIST_CENTER_Y_FIXED  132.0
#endif
#define FOCAL_LENGTH_FIXED   1310.0
#define CAL_MAT_0_FIXED      1.0
#define CAL_MAT_1_FIXED      0.0
#define CAL_MAT_2_FIXED      0.0
#define CAL_MAT_3_FIXED      0.0
#define CAL_MAT_4_FIXED      1.0
#define CAL_MAT_5_FIXED      0.0
#define CAL_MAT_6_FIXED      0.0
#define CAL_MAT_7_FIXED      0.0
#define CAL_MAT_8_FIXED      1.0
#define CAL_MAT_9_FIXED      0.0
#define CAL_MAT_10_FIXED     0.0
#define CAL_MAT_11_FIXED     0.0
*/

// TDA3x
#define BASELINE_FIXED 12.0
#define SCALE_FACTOR_X_FIXED 1.7391
#define SCALE_FACTOR_Y_FIXED 1.8750
#define DIST_CENTER_X_FIXED  368.0
#define DIST_CENTER_Y_FIXED  192.0
#define FOCAL_LENGTH_FIXED   1310.0
#define CAL_MAT_0_FIXED      1.0
#define CAL_MAT_1_FIXED      0.0
#define CAL_MAT_2_FIXED      0.0
#define CAL_MAT_3_FIXED      0.0
#define CAL_MAT_4_FIXED      1.0
#define CAL_MAT_5_FIXED      0.0
#define CAL_MAT_6_FIXED      0.0
#define CAL_MAT_7_FIXED      0.0
#define CAL_MAT_8_FIXED      1.0
#define CAL_MAT_9_FIXED      0.0
#define CAL_MAT_10_FIXED     0.0
#define CAL_MAT_11_FIXED     0.0


/**
 ******************************************************************************
 *
 * \brief This structure gathers all the different image dimensions used throughout the
 *          stereo-vision processing. It is initialized by the function ChainsCommon_Stereo_initImageDims()
 *
 ******************************************************************************
 */
typedef struct {
    UInt32 disparityOutputRoiWidth; /* Input parameter */
    UInt32 disparityOutputRoiHeight; /* Input parameter */

    UInt32 disparityInputImageWidth;
    UInt32 disparityInputImageHeight;
    UInt32 disparityInputLeftImageStartX;
    UInt32 disparityInputLeftImageStartY;
    UInt32 disparityInputRightImageStartX;
    UInt32 disparityInputRightImageStartY;
    UInt32 censusOutputRoiWidth;
    UInt32 censusOutputRoiHeight;
    UInt32 censusInputImageWidth;
    UInt32 censusInputImageHeight;
    UInt32 censusInputImageStartX;
    UInt32 censusInputImageStartY;
    UInt32 remapImageWidth;
    UInt32 remapImageHeight;
    UInt32 origRoiStartX;
    UInt32 origRoiStartY;
}StereoImageDims;
extern StereoImageDims gStereoImDims;


/*NOTE: This struct is also defined in netwrork_ctrl tools in network_ctrl_handle_stereo_set_params.c .
It contains the parameters of the census transform and disparity computation algorithms that are set
once a use case is started. These parameters cannot be changed until the use case is stopped and then restarted.
Please make sure the two are matching, if any changes are made.
 */
typedef struct
{
    UInt32              numDisparities;
    UInt32              disparityStepSize;
    Uint32              disparitySearchDir;
    UInt32              disparitySupportWinWidth;
    UInt32              disparitySupportWinHeight;
    UInt32              leftRightCheckEna;
    UInt32              censusWinWidth;
    UInt32              censusWinHeight;
    UInt32              censusWinHorzStep;
    UInt32              censusWinVertStep;
    UInt32              postproc_colormap_index;
}Stereo_ConfigurableCreateParams;

extern Stereo_ConfigurableCreateParams gStereoParams;

/**
 ******************************************************************************
 *
 * \brief set default parameters for stereo. If user passes any parameters then these are 
 *          configured instead.
 *
 * \param  pPrm  [IN]  Stereo specific Params
 *
 ******************************************************************************
 */
static inline void Stereo_CreateParams_Init
(Stereo_ConfigurableCreateParams *pPrm)
{
    if(pPrm == NULL)
    {
        gStereoParams.numDisparities 
        = NUM_DISPARITIES;
        gStereoParams.disparitySearchDir
        = DISPARITY_SEARCH_DIR;
        gStereoParams.disparityStepSize
        = DISPARITY_STEP_SIZE;
        gStereoParams.disparitySupportWinWidth
        = DISPARITY_WIN_WIDTH;
        gStereoParams.disparitySupportWinHeight
        = DISPARITY_WIN_HEIGHT;
        gStereoParams.leftRightCheckEna
        = DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP;
        gStereoParams.censusWinWidth
        = CENSUS_WIN_WIDTH;
        gStereoParams.censusWinHeight
        = CENSUS_WIN_HEIGHT;
        gStereoParams.censusWinHorzStep
        = CENSUS_WIN_HORZ_STEP;
        gStereoParams.censusWinVertStep
        = CENSUS_WIN_VERT_STEP;
        gStereoParams.postproc_colormap_index 
        = POSTPROC_COLORMAP_INDEX;
    }
    else
    {
        memcpy(&gStereoParams, pPrm, sizeof(Stereo_ConfigurableCreateParams));
    }
}


typedef enum
{
    NUM_DISPARITIES_SD,
    DISPARITY_STEP_SIZE_SD,
    DISPARITY_SEARCH_DIR_SD,
    DISPARITY_WIN_WIDTH_SD,
    DISPARITY_WIN_HEIGHT_SD,
    DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP_SD,
    CENSUS_WIN_WIDTH_SD,
    CENSUS_WIN_HEIGHT_SD,
    CENSUS_WIN_HORZ_STEP_SD,
    CENSUS_WIN_VERT_STEP_SD,
    POSTPROC_COST_MAX_THRESHOLD_SD,
    POSTPROC_CONF_MIN_THRSESHOLD_SD,
    POSTPROC_TEXTURE_LUMALOTHRESH_SD,
    POSTPROC_TEXTURE_LUMAHITHRESH_SD,
    POSTPROC_TEXTURE_THRESHOLD_SD,
    POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD_SD,
    POSTPROC_MAX_DISP_DISSIMILARITY_SD,
    POSTPROC_MIN_CONFIDENT_N_SEG_SD,
    POSTPROC_HOLEFILLING_STRENGTH_SD,
    POSTPROC_TEMPORAL_FILTER_NUM_FRAMES_SD,
    POSTPROC_MIN_DISPARITY_DISPLAY_SD,
    POSTPROC_COLORMAP_INDEX_SD,
    REMAP_OUTPUT_BLOCK_WIDTH_SD,
    REMAP_OUTPUT_BLOCK_HEIGHT_SD,
    NUM_SPARAMS_IN_SD // number of stereo params in SD
} STEREO_PARAMS_SD;

typedef enum
{
    BASELINE_SD,
    SCALE_FACTOR_X_SD,
    SCALE_FACTOR_Y_SD,
    DIST_CENTER_X_SD,
    DIST_CENTER_Y_SD,
    FOCAL_LENGTH,
    CAL_MAT_0_SD,
    CAL_MAT_1_SD,
    CAL_MAT_2_SD,
    CAL_MAT_3_SD,
    CAL_MAT_4_SD,
    CAL_MAT_5_SD,
    CAL_MAT_6_SD,
    CAL_MAT_7_SD,
    CAL_MAT_8_SD,
    CAL_MAT_9_SD,
    CAL_MAT_10_SD,
    CAL_MAT_11_SD,
    NUM_SCPARAMS_IN_SD,
} STEREO_CAMPARAMS_SD;

/**
 ******************************************************************************
 *
 * \brief This structure gathers all stereo parameters from SD card in
 *        ChainsCommon_Stereo_Read_Params()
 *
 ******************************************************************************
 */
typedef struct
{
    UInt32              numParams;
    UInt32              stereoParamsSD[NUM_SPARAMS_IN_SD];
}Stereo_CreateParamsFromSD;

/**
 ******************************************************************************
 *
 * \brief This structure gathers all stereo camera parameters from SD card in
 *        ChainsCommon_Stereo_Read_CamParams()
 *
 ******************************************************************************
 */
typedef struct
{
    UInt32              numParams;
    float               stereoCamParamsSD[NUM_SCPARAMS_IN_SD];
}Stereo_CreateCamParamsFromSD;

#endif /* _chains_vipStereoCameraDisplay_Defines_H_ */
