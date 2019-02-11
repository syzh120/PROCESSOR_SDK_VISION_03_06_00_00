
/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2016 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ti/vlib/src/common/VLIB_test.h>
#include <ti/vlib/src/common/VLIB_memory.h>
#include <ti/vlib/src/common/VLIB_profile.h>
#include <ti/vlib/vlib.h>

#define LEVEL_OF_FEEDBACK (0)   /* No printing of Output vectors */

extern VLIB_afast12_detectCorners_d();
extern VLIB_afast9_detectCorners_d();
extern VLIB_aFast_nonmaxSuppression_d();
extern VLIB_bhattacharyaDistance_F32_d();
extern VLIB_bhattacharyaDistance_U32_d();
extern VLIB_binarySkeleton_d();
extern VLIB_blobAnalysis_d();
extern VLIB_blockMedian_d();
extern VLIB_blockStatistics_d();
extern VLIB_Canny_Edge_Detection_d();
extern VLIB_Connected_Components_Labeling_d();
extern VLIB_convertUYVYint_to_HSLpl_d();
extern VLIB_convertUYVYint_to_LABpl_d();
extern VLIB_convertUYVYint_to_LABpl_LUT_d();
extern VLIB_convertUYVYint_to_RGBpl_d();
extern VLIB_convertUYVYint_to_YUV420pl_d();
extern VLIB_convertUYVYint_to_YUV422pl_d();
extern VLIB_convertUYVYint_to_YUV444pl_d();
extern VLIB_convertUYVYpl_to_YUVint_d();
extern VLIB_convertUYVYsemipl_to_YUVpl_d();
extern VLIB_convert_NV12_to_RGBpl_tile_d();
extern VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d();
extern VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile_d();
extern VLIB_coOccurrenceMatrix_d();
extern VLIB_dilate_bin_cross_d();
extern VLIB_dilate_bin_mask_d();
extern VLIB_dilate_bin_square_d();
extern VLIB_disparity_SAD16_d();
extern VLIB_disparity_SAD8_d();
extern VLIB_disparity_SAD_firstRow16_d();
extern VLIB_disparity_SAD_firstRow8_d();
extern VLIB_erode_bin_cross_d();
extern VLIB_erode_bin_mask_d();
extern VLIB_erode_bin_singlePixel_d();
extern VLIB_erode_bin_square_d();
extern VLIB_extract8bitBackgroundS16_d();
extern VLIB_extractLumaFromUYUV_d();
extern VLIB_extractLumaFromYUYV_d();
extern VLIB_findFundamentalMat_d();
extern VLIB_gauss5x5PyramidKernel_16_d();
extern VLIB_gauss5x5PyramidKernel_8_d();
extern VLIB_goodFeaturestoTrack_d();
extern VLIB_gradientH5x5PyramidKernel_8_d();
extern VLIB_gradientV5x5PyramidKernel_8_d();
extern VLIB_grayscale_morphology_d();
extern VLIB_haarDetectObjectsDense_d();
extern VLIB_haarDetectObjectsSparse_d();
extern VLIB_hammingDistance_d();
extern VLIB_harrisScore_7x7_d();
extern VLIB_harrisScore_7x7_S32_d();
extern VLIB_histogram_1D_Init_U16_d();
extern VLIB_histogram_1D_Init_U8_d();
extern VLIB_histogram_1D_U16_d();
extern VLIB_histogram_1D_U8_d();
extern VLIB_histogram_equal_8_d();
extern VLIB_histogram_equal_8_f32_d();
extern VLIB_histogram_nD_U16_d();
extern VLIB_homographyDecomposition_d();
extern VLIB_houghLineFromList_d();
extern VLIB_hysteresisThresholding_d();
extern VLIB_imagePyramid16_d();
extern VLIB_imagePyramid8_d();
extern VLIB_image_rescale_d();
extern VLIB_initMeanWithLumaS16_d();
extern VLIB_initMeanWithLumaS32_d();
extern VLIB_initUYVYint_to_LABpl_LUT_d();
extern VLIB_initVarWithConstS16_d();
extern VLIB_initVarWithConstS32_d();
extern VLIB_insertLumaIntoYUYV_d();
extern VLIB_integralImage16_d();
extern VLIB_integralImage8_d();
extern VLIB_kalmanFilter_1x2_Correct_F32_d();
extern VLIB_kalmanFilter_1x2_Predict_F32_d();
extern VLIB_kalmanFilter_2x4_Correct_d();
extern VLIB_kalmanFilter_2x4_Correct_F32_d();
extern VLIB_kalmanFilter_2x4_Correct_S16_F32_d();
extern VLIB_kalmanFilter_2x4_Predict_d();
extern VLIB_kalmanFilter_2x4_Predict_F32_d();
extern VLIB_kalmanFilter_2x4_Predict_S16_F32_d();
extern VLIB_kalmanFilter_4x12_Correct_F32_d();
extern VLIB_kalmanFilter_4x12_Predict_F32_d();
extern VLIB_kalmanFilter_4x6_Correct_d();
extern VLIB_kalmanFilter_4x6_Correct_F32_d();
extern VLIB_kalmanFilter_4x6_Correct_S16_F32_d();
extern VLIB_kalmanFilter_4x6_Predict_d();
extern VLIB_kalmanFilter_4x6_Predict_F32_d();
extern VLIB_kalmanFilter_4x6_Predict_S16_F32_d();
extern VLIB_kalmanFilter_4x8_Correct_F32_d();
extern VLIB_kalmanFilter_4x8_Predict_F32_d();
extern VLIB_L1DistanceS16_d();
extern VLIB_L2_norm_f32_d();
extern VLIB_L2_norm_i16_d();
extern VLIB_L2_norm_i32_d();
extern VLIB_L2_norm_i8_d();
extern VLIB_lbp_d();
extern VLIB_legendreMoments_d();
extern VLIB_legendreMoments_Init_d();
extern VLIB_matchTemplate_d();
extern VLIB_mixtureOfGaussiansS16_d();
extern VLIB_mixtureOfGaussiansS32_d();
extern VLIB_neuralNet_tile_d();
extern VLIB_nonMaxSuppress_3x3_S16_d();
extern VLIB_nonMaxSuppress_5x5_S16_d();
extern VLIB_nonMaxSuppress_7x7_S16_d();
extern VLIB_nonMaxSuppress_U16_d();
extern VLIB_nonMaxSuppress_U32_d();
extern VLIB_normalFlow_16_d();
extern VLIB_normalize_input_i8u_o16s_tile_d();
extern VLIB_ORB_bestFeaturesToFront_d();
extern VLIB_ORB_computeOrientation_d();
extern VLIB_ORB_computeRBrief_d();
extern VLIB_ORB_getHarrisScore_d();
extern VLIB_originalfast12_detectCorners_d();
extern VLIB_originalfast12_score_d();
extern VLIB_originalfast9_detectCorners_d();
extern VLIB_originalfast9_score_d();
extern VLIB_packMask32_d();
extern VLIB_recursiveFilterHoriz1stOrderS16_d();
extern VLIB_recursiveFilterHoriz1stOrder_d();
extern VLIB_recursiveFilterVert1stOrderS16_d();
extern VLIB_recursiveFilterVert1stOrder_d();
extern VLIB_ReLU_MaxPooling_2x2_skip2_tile_d();
extern VLIB_simplex_3D_d();
extern VLIB_simplex_d();
extern VLIB_subtractBackgroundS16_d();
extern VLIB_subtractBackgroundS32_d();
extern VLIB_trackFeaturesLucasKanade_7x7_d();
extern VLIB_triangulatePoints_d();
extern VLIB_unpackMask32_d();
extern VLIB_updateEWRMeanS16_d();
extern VLIB_updateEWRMeanS32_d();
extern VLIB_updateEWRVarianceS16_d();
extern VLIB_updateEWRVarianceS32_d();
extern VLIB_updateUWRMeanS16_d();
extern VLIB_updateUWRVarianceS16_d();
extern VLIB_weightedHistogram_1D_U16_d();
extern VLIB_weightedHistogram_1D_U8_d();
extern VLIB_weightedHistogram_nD_U16_d();
extern VLIB_xyGradientsAndMagnitude_d();
extern VLIB_xyGradients_d();
extern VLIB_xyGradients_Magnitude_Orientations_d();


void main()
{
  VLIB_cache_init();

  	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_afast12_detectCorners     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_afast12_detectCorners_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_afast9_detectCorners     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_afast9_detectCorners_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_aFast_nonmaxSuppression     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_aFast_nonmaxSuppression_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_bhattacharyaDistance_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_bhattacharyaDistance_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_bhattacharyaDistance_U32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_bhattacharyaDistance_U32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_binarySkeleton     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_binarySkeleton_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_blobAnalysis     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_blobAnalysis_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_blockMedian     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_blockMedian_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_blockStatistics     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_blockStatistics_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_Canny_Edge_Detection     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_Canny_Edge_Detection_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_Connected_Components_Labeling     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_Connected_Components_Labeling_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_HSLpl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_HSLpl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_LABpl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_LABpl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_LABpl_LUT     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_LABpl_LUT_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_RGBpl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_RGBpl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_YUV420pl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_YUV420pl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_YUV422pl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_YUV422pl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYint_to_YUV444pl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYint_to_YUV444pl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYpl_to_YUVint     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYpl_to_YUVint_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convertUYVYsemipl_to_YUVpl     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convertUYVYsemipl_to_YUVpl_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_convert_NV12_to_RGBpl_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_convert_NV12_to_RGBpl_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_coOccurrenceMatrix     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_coOccurrenceMatrix_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_dilate_bin_cross     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_dilate_bin_cross_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_dilate_bin_mask     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_dilate_bin_mask_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_dilate_bin_square     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_dilate_bin_square_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_disparity_SAD16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_disparity_SAD16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_disparity_SAD8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_disparity_SAD8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_disparity_SAD_firstRow16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_disparity_SAD_firstRow16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_disparity_SAD_firstRow8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_disparity_SAD_firstRow8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_erode_bin_cross     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_erode_bin_cross_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_erode_bin_mask     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_erode_bin_mask_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_erode_bin_singlePixel     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_erode_bin_singlePixel_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_erode_bin_square     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_erode_bin_square_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_extract8bitBackgroundS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_extract8bitBackgroundS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_extractLumaFromUYUV     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_extractLumaFromUYUV_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_extractLumaFromYUYV     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_extractLumaFromYUYV_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_findFundamentalMat     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_findFundamentalMat_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_gauss5x5PyramidKernel_16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_gauss5x5PyramidKernel_16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_gauss5x5PyramidKernel_8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_gauss5x5PyramidKernel_8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_goodFeaturestoTrack     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_goodFeaturestoTrack_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_gradientH5x5PyramidKernel_8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_gradientH5x5PyramidKernel_8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_gradientV5x5PyramidKernel_8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_gradientV5x5PyramidKernel_8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_grayscale_morphology     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_grayscale_morphology_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_haarDetectObjectsDense     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_haarDetectObjectsDense_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_haarDetectObjectsSparse     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_haarDetectObjectsSparse_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_hammingDistance     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_hammingDistance_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_harrisScore_7x7     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_harrisScore_7x7_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_harrisScore_7x7_S32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_harrisScore_7x7_S32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_1D_Init_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_1D_Init_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_1D_Init_U8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_1D_Init_U8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_1D_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_1D_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_1D_U8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_1D_U8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_equal_8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_equal_8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_equal_8_f32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_equal_8_f32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_histogram_nD_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_histogram_nD_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_homographyDecomposition     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_homographyDecomposition_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_houghLineFromList     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_houghLineFromList_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_hysteresisThresholding     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_hysteresisThresholding_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_imagePyramid16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_imagePyramid16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_imagePyramid8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_imagePyramid8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_image_rescale     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_image_rescale_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_initMeanWithLumaS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_initMeanWithLumaS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_initMeanWithLumaS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_initMeanWithLumaS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_initUYVYint_to_LABpl_LUT     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_initUYVYint_to_LABpl_LUT_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_initVarWithConstS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_initVarWithConstS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_initVarWithConstS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_initVarWithConstS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_insertLumaIntoYUYV     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_insertLumaIntoYUYV_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_integralImage16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_integralImage16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_integralImage8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_integralImage8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_1x2_Correct_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_1x2_Correct_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_1x2_Predict_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_1x2_Predict_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Correct     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Correct_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Correct_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Correct_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Correct_S16_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Correct_S16_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Predict     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Predict_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Predict_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Predict_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_2x4_Predict_S16_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_2x4_Predict_S16_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x12_Correct_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x12_Correct_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x12_Predict_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x12_Predict_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Correct     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Correct_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Correct_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Correct_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Correct_S16_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Correct_S16_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Predict     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Predict_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Predict_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Predict_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x6_Predict_S16_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x6_Predict_S16_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x8_Correct_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x8_Correct_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_kalmanFilter_4x8_Predict_F32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_kalmanFilter_4x8_Predict_F32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_L1DistanceS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_L1DistanceS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_L2_norm_f32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_L2_norm_f32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_L2_norm_i16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_L2_norm_i16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_L2_norm_i32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_L2_norm_i32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_L2_norm_i8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_L2_norm_i8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_lbp     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_lbp_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_legendreMoments     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_legendreMoments_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_legendreMoments_Init     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_legendreMoments_Init_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_matchTemplate     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_matchTemplate_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_mixtureOfGaussiansS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_mixtureOfGaussiansS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_mixtureOfGaussiansS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_mixtureOfGaussiansS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_neuralNet_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_neuralNet_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_nonMaxSuppress_3x3_S16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_nonMaxSuppress_3x3_S16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_nonMaxSuppress_5x5_S16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_nonMaxSuppress_5x5_S16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_nonMaxSuppress_7x7_S16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_nonMaxSuppress_7x7_S16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_nonMaxSuppress_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_nonMaxSuppress_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_nonMaxSuppress_U32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_nonMaxSuppress_U32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_normalFlow_16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_normalFlow_16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_normalize_input_i8u_o16s_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_normalize_input_i8u_o16s_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_ORB_bestFeaturesToFront     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_ORB_bestFeaturesToFront_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_ORB_computeOrientation     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_ORB_computeOrientation_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_ORB_computeRBrief     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_ORB_computeRBrief_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_ORB_getHarrisScore     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_ORB_getHarrisScore_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_originalfast12_detectCorners     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_originalfast12_detectCorners_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_originalfast12_score     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_originalfast12_score_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_originalfast9_detectCorners     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_originalfast9_detectCorners_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_originalfast9_score     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_originalfast9_score_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_packMask32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_packMask32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_recursiveFilterHoriz1stOrderS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_recursiveFilterHoriz1stOrderS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_recursiveFilterHoriz1stOrder     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_recursiveFilterHoriz1stOrder_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_recursiveFilterVert1stOrderS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_recursiveFilterVert1stOrderS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_recursiveFilterVert1stOrder     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_recursiveFilterVert1stOrder_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_ReLU_MaxPooling_2x2_skip2_tile     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_ReLU_MaxPooling_2x2_skip2_tile_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_simplex_3D     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_simplex_3D_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_simplex     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_simplex_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_subtractBackgroundS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_subtractBackgroundS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_subtractBackgroundS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_subtractBackgroundS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_trackFeaturesLucasKanade_7x7     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_trackFeaturesLucasKanade_7x7_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_triangulatePoints     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_triangulatePoints_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_unpackMask32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_unpackMask32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateEWRMeanS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateEWRMeanS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateEWRMeanS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateEWRMeanS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateEWRVarianceS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateEWRVarianceS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateEWRVarianceS32     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateEWRVarianceS32_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateUWRMeanS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateUWRMeanS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_updateUWRVarianceS16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_updateUWRVarianceS16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_weightedHistogram_1D_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_weightedHistogram_1D_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_weightedHistogram_1D_U8     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_weightedHistogram_1D_U8_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_weightedHistogram_nD_U16     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_weightedHistogram_nD_U16_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_xyGradientsAndMagnitude     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_xyGradientsAndMagnitude_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_xyGradients     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_xyGradients_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VLIB_xyGradients_Magnitude_Orientations     |\n");
	printf(" +---------------------------------------+\n\n");
	VLIB_xyGradients_Magnitude_Orientations_d(LEVEL_OF_FEEDBACK);


}
