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
**|        Copyright (c) 2007 - 2017 Texas Instruments Incorporated          |**
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
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ti/vlib/src/VLIB_afast12_detectCorners/VLIB_afast12_detectCorners.h>
#include <ti/vlib/src/VLIB_afast9_detectCorners/VLIB_afast9_detectCorners.h>
#include <ti/vlib/src/VLIB_aFast_nonmaxSuppression/VLIB_aFast_nonmaxSuppression.h>
#include <ti/vlib/src/VLIB_bhattacharyaDistance_F32/VLIB_bhattacharyaDistance_F32.h>
#include <ti/vlib/src/VLIB_bhattacharyaDistance_U32/VLIB_bhattacharyaDistance_U32.h>
#include <ti/vlib/src/VLIB_binarySkeleton/VLIB_binarySkeleton.h>
#include <ti/vlib/src/VLIB_blobAnalysis/VLIB_blobAnalysis.h>
#include <ti/vlib/src/VLIB_blockMedian/VLIB_blockMedian.h>
#include <ti/vlib/src/VLIB_blockStatistics/VLIB_blockStatistics.h>
#include <ti/vlib/src/VLIB_Canny_Edge_Detection/VLIB_Canny_Edge_Detection.h>
#include <ti/vlib/src/VLIB_Connected_Components_Labeling/VLIB_Connected_Components_Labeling.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_HSLpl/VLIB_convertUYVYint_to_HSLpl.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_LABpl/VLIB_convertUYVYint_to_LABpl.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_LABpl_LUT/VLIB_convertUYVYint_to_LABpl_LUT.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_RGBpl/VLIB_convertUYVYint_to_RGBpl.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_YUV420pl/VLIB_convertUYVYint_to_YUV420pl.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_YUV422pl/VLIB_convertUYVYint_to_YUV422pl.h>
#include <ti/vlib/src/VLIB_convertUYVYint_to_YUV444pl/VLIB_convertUYVYint_to_YUV444pl.h>
#include <ti/vlib/src/VLIB_convertUYVYpl_to_YUVint/VLIB_convertUYVYpl_to_YUVint.h>
#include <ti/vlib/src/VLIB_convertUYVYsemipl_to_YUVpl/VLIB_convertUYVYsemipl_to_YUVpl.h>
#include <ti/vlib/src/VLIB_convert_NV12_to_RGBpl_tile/VLIB_convert_NV12_to_RGBpl_tile.h>
#include <ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile.h>
#include <ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile.h>
#include <ti/vlib/src/VLIB_coOccurrenceMatrix/VLIB_coOccurrenceMatrix.h>
#include <ti/vlib/src/VLIB_dilate_bin_cross/VLIB_dilate_bin_cross.h>
#include <ti/vlib/src/VLIB_dilate_bin_mask/VLIB_dilate_bin_mask.h>
#include <ti/vlib/src/VLIB_dilate_bin_square/VLIB_dilate_bin_square.h>
#include <ti/vlib/src/VLIB_disparity_SAD16/VLIB_disparity_SAD16.h>
#include <ti/vlib/src/VLIB_disparity_SAD8/VLIB_disparity_SAD8.h>
#include <ti/vlib/src/VLIB_disparity_SAD_firstRow16/VLIB_disparity_SAD_firstRow16.h>
#include <ti/vlib/src/VLIB_disparity_SAD_firstRow8/VLIB_disparity_SAD_firstRow8.h>
#include <ti/vlib/src/VLIB_erode_bin_cross/VLIB_erode_bin_cross.h>
#include <ti/vlib/src/VLIB_erode_bin_mask/VLIB_erode_bin_mask.h>
#include <ti/vlib/src/VLIB_erode_bin_singlePixel/VLIB_erode_bin_singlePixel.h>
#include <ti/vlib/src/VLIB_erode_bin_square/VLIB_erode_bin_square.h>
#include <ti/vlib/src/VLIB_extract8bitBackgroundS16/VLIB_extract8bitBackgroundS16.h>
#include <ti/vlib/src/VLIB_extractLumaFromUYUV/VLIB_extractLumaFromUYUV.h>
#include <ti/vlib/src/VLIB_extractLumaFromYUYV/VLIB_extractLumaFromYUYV.h>
#include <ti/vlib/src/VLIB_findFundamentalMat/VLIB_findFundamentalMat.h>
#include <ti/vlib/src/VLIB_gauss5x5PyramidKernel_16/VLIB_gauss5x5PyramidKernel_16.h>
#include <ti/vlib/src/VLIB_gauss5x5PyramidKernel_8/VLIB_gauss5x5PyramidKernel_8.h>
#include <ti/vlib/src/VLIB_goodFeaturestoTrack/VLIB_goodFeaturestoTrack.h>
#include <ti/vlib/src/VLIB_gradientH5x5PyramidKernel_8/VLIB_gradientH5x5PyramidKernel_8.h>
#include <ti/vlib/src/VLIB_gradientV5x5PyramidKernel_8/VLIB_gradientV5x5PyramidKernel_8.h>
#include <ti/vlib/src/VLIB_grayscale_morphology/VLIB_grayscale_morphology.h>
#include <ti/vlib/src/VLIB_haarDetectObjectsDense/VLIB_haarDetectObjectsDense.h>
#include <ti/vlib/src/VLIB_haarDetectObjectsSparse/VLIB_haarDetectObjectsSparse.h>
#include <ti/vlib/src/VLIB_hammingDistance/VLIB_hammingDistance.h>
#include <ti/vlib/src/VLIB_harrisScore_7x7/VLIB_harrisScore_7x7.h>
#include <ti/vlib/src/VLIB_harrisScore_7x7_S32/VLIB_harrisScore_7x7_S32.h>
#include <ti/vlib/src/VLIB_histogram_1D_Init_U16/VLIB_histogram_1D_Init_U16.h>
#include <ti/vlib/src/VLIB_histogram_1D_Init_U8/VLIB_histogram_1D_Init_U8.h>
#include <ti/vlib/src/VLIB_histogram_1D_U16/VLIB_histogram_1D_U16.h>
#include <ti/vlib/src/VLIB_histogram_1D_U8/VLIB_histogram_1D_U8.h>
#include <ti/vlib/src/VLIB_histogram_equal_8/VLIB_histogram_equal_8.h>
#include <ti/vlib/src/VLIB_histogram_equal_8_f32/VLIB_histogram_equal_8_f32.h>
#include <ti/vlib/src/VLIB_histogram_nD_U16/VLIB_histogram_nD_U16.h>
#include <ti/vlib/src/VLIB_homographyDecomposition/VLIB_homographyDecomposition.h>
#include <ti/vlib/src/VLIB_houghLineFromList/VLIB_houghLineFromList.h>
#include <ti/vlib/src/VLIB_hysteresisThresholding/VLIB_hysteresisThresholding.h>
#include <ti/vlib/src/VLIB_imagePyramid16/VLIB_imagePyramid16.h>
#include <ti/vlib/src/VLIB_imagePyramid8/VLIB_imagePyramid8.h>
#include <ti/vlib/src/VLIB_image_rescale/VLIB_image_rescale.h>
#include <ti/vlib/src/VLIB_initMeanWithLumaS16/VLIB_initMeanWithLumaS16.h>
#include <ti/vlib/src/VLIB_initMeanWithLumaS32/VLIB_initMeanWithLumaS32.h>
#include <ti/vlib/src/VLIB_initUYVYint_to_LABpl_LUT/VLIB_initUYVYint_to_LABpl_LUT.h>
#include <ti/vlib/src/VLIB_initVarWithConstS16/VLIB_initVarWithConstS16.h>
#include <ti/vlib/src/VLIB_initVarWithConstS32/VLIB_initVarWithConstS32.h>
#include <ti/vlib/src/VLIB_insertLumaIntoYUYV/VLIB_insertLumaIntoYUYV.h>
#include <ti/vlib/src/VLIB_integralImage16/VLIB_integralImage16.h>
#include <ti/vlib/src/VLIB_integralImage8/VLIB_integralImage8.h>
#include <ti/vlib/src/VLIB_kalmanFilter_1x2_Correct_F32/VLIB_kalmanFilter_1x2_Correct_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_1x2_Predict_F32/VLIB_kalmanFilter_1x2_Predict_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Correct/VLIB_kalmanFilter_2x4_Correct.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_F32/VLIB_kalmanFilter_2x4_Correct_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_S16_F32/VLIB_kalmanFilter_2x4_Correct_S16_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Predict/VLIB_kalmanFilter_2x4_Predict.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_F32/VLIB_kalmanFilter_2x4_Predict_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_S16_F32/VLIB_kalmanFilter_2x4_Predict_S16_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x12_Correct_F32/VLIB_kalmanFilter_4x12_Correct_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x12_Predict_F32/VLIB_kalmanFilter_4x12_Predict_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Correct/VLIB_kalmanFilter_4x6_Correct.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_F32/VLIB_kalmanFilter_4x6_Correct_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_S16_F32/VLIB_kalmanFilter_4x6_Correct_S16_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Predict/VLIB_kalmanFilter_4x6_Predict.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_F32/VLIB_kalmanFilter_4x6_Predict_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_S16_F32/VLIB_kalmanFilter_4x6_Predict_S16_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x8_Correct_F32/VLIB_kalmanFilter_4x8_Correct_F32.h>
#include <ti/vlib/src/VLIB_kalmanFilter_4x8_Predict_F32/VLIB_kalmanFilter_4x8_Predict_F32.h>
#include <ti/vlib/src/VLIB_L1DistanceS16/VLIB_L1DistanceS16.h>
#include <ti/vlib/src/VLIB_L2_norm_f32/VLIB_L2_norm_f32.h>
#include <ti/vlib/src/VLIB_L2_norm_i16/VLIB_L2_norm_i16.h>
#include <ti/vlib/src/VLIB_L2_norm_i32/VLIB_L2_norm_i32.h>
#include <ti/vlib/src/VLIB_L2_norm_i8/VLIB_L2_norm_i8.h>
#include <ti/vlib/src/VLIB_lbp/VLIB_lbp.h>
#include <ti/vlib/src/VLIB_legendreMoments/VLIB_legendreMoments.h>
#include <ti/vlib/src/VLIB_legendreMoments_Init/VLIB_legendreMoments_Init.h>
#include <ti/vlib/src/VLIB_matchTemplate/VLIB_matchTemplate.h>
#include <ti/vlib/src/VLIB_mixtureOfGaussiansS16/VLIB_mixtureOfGaussiansS16.h>
#include <ti/vlib/src/VLIB_mixtureOfGaussiansS32/VLIB_mixtureOfGaussiansS32.h>
#include <ti/vlib/src/VLIB_neuralNet_tile/VLIB_neuralNet_tile.h>
#include <ti/vlib/src/VLIB_nonMaxSuppress_3x3_S16/VLIB_nonMaxSuppress_3x3_S16.h>
#include <ti/vlib/src/VLIB_nonMaxSuppress_5x5_S16/VLIB_nonMaxSuppress_5x5_S16.h>
#include <ti/vlib/src/VLIB_nonMaxSuppress_7x7_S16/VLIB_nonMaxSuppress_7x7_S16.h>
#include <ti/vlib/src/VLIB_nonMaxSuppress_U16/VLIB_nonMaxSuppress_U16.h>
#include <ti/vlib/src/VLIB_nonMaxSuppress_U32/VLIB_nonMaxSuppress_U32.h>
#include <ti/vlib/src/VLIB_normalFlow_16/VLIB_normalFlow_16.h>
#include <ti/vlib/src/VLIB_normalize_input_i8u_o16s_tile/VLIB_normalize_input_i8u_o16s_tile.h>
#include <ti/vlib/src/VLIB_ORB_bestFeaturesToFront/VLIB_ORB_bestFeaturesToFront.h>
#include <ti/vlib/src/VLIB_ORB_computeOrientation/VLIB_ORB_computeOrientation.h>
#include <ti/vlib/src/VLIB_ORB_computeRBrief/VLIB_ORB_computeRBrief.h>
#include <ti/vlib/src/VLIB_ORB_getHarrisScore/VLIB_ORB_getHarrisScore.h>
#include <ti/vlib/src/VLIB_originalfast12_detectCorners/VLIB_originalfast12_detectCorners.h>
#include <ti/vlib/src/VLIB_originalfast12_score/VLIB_originalfast12_score.h>
#include <ti/vlib/src/VLIB_originalfast9_detectCorners/VLIB_originalfast9_detectCorners.h>
#include <ti/vlib/src/VLIB_originalfast9_score/VLIB_originalfast9_score.h>
#include <ti/vlib/src/VLIB_packMask32/VLIB_packMask32.h>
#include <ti/vlib/src/VLIB_recursiveFilterHoriz1stOrderS16/VLIB_recursiveFilterHoriz1stOrderS16.h>
#include <ti/vlib/src/VLIB_recursiveFilterHoriz1stOrder/VLIB_recursiveFilterHoriz1stOrder.h>
#include <ti/vlib/src/VLIB_recursiveFilterVert1stOrderS16/VLIB_recursiveFilterVert1stOrderS16.h>
#include <ti/vlib/src/VLIB_recursiveFilterVert1stOrder/VLIB_recursiveFilterVert1stOrder.h>
#include <ti/vlib/src/VLIB_ReLU_MaxPooling_2x2_skip2_tile/VLIB_ReLU_MaxPooling_2x2_skip2_tile.h>
#include <ti/vlib/src/VLIB_simplex_3D/VLIB_simplex_3D.h>
#include <ti/vlib/src/VLIB_simplex/VLIB_simplex.h>
#include <ti/vlib/src/VLIB_subtractBackgroundS16/VLIB_subtractBackgroundS16.h>
#include <ti/vlib/src/VLIB_subtractBackgroundS32/VLIB_subtractBackgroundS32.h>
#include <ti/vlib/src/VLIB_trackFeaturesLucasKanade_7x7/VLIB_trackFeaturesLucasKanade_7x7.h>
#include <ti/vlib/src/VLIB_triangulatePoints/VLIB_triangulatePoints.h>
#include <ti/vlib/src/VLIB_unpackMask32/VLIB_unpackMask32.h>
#include <ti/vlib/src/VLIB_updateEWRMeanS16/VLIB_updateEWRMeanS16.h>
#include <ti/vlib/src/VLIB_updateEWRMeanS32/VLIB_updateEWRMeanS32.h>
#include <ti/vlib/src/VLIB_updateEWRVarianceS16/VLIB_updateEWRVarianceS16.h>
#include <ti/vlib/src/VLIB_updateEWRVarianceS32/VLIB_updateEWRVarianceS32.h>
#include <ti/vlib/src/VLIB_updateUWRMeanS16/VLIB_updateUWRMeanS16.h>
#include <ti/vlib/src/VLIB_updateUWRVarianceS16/VLIB_updateUWRVarianceS16.h>
#include <ti/vlib/src/VLIB_weightedHistogram_1D_U16/VLIB_weightedHistogram_1D_U16.h>
#include <ti/vlib/src/VLIB_weightedHistogram_1D_U8/VLIB_weightedHistogram_1D_U8.h>
#include <ti/vlib/src/VLIB_weightedHistogram_nD_U16/VLIB_weightedHistogram_nD_U16.h>
#include <ti/vlib/src/VLIB_xyGradientsAndMagnitude/VLIB_xyGradientsAndMagnitude.h>
#include <ti/vlib/src/VLIB_xyGradients/VLIB_xyGradients.h>
#include <ti/vlib/src/VLIB_xyGradients_Magnitude_Orientations/VLIB_xyGradients_Magnitude_Orientations.h>

#ifdef __cplusplus
}
#endif /* __cplusplus */

