
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
**|        Copyright (c) 2017 Texas Instruments Incorporated                 |**
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
#include <ti/vxlib/src/common/TI_test.h>
#include <ti/vxlib/src/common/TI_memory.h>
#include <ti/vxlib/src/common/TI_profile.h>
#include <ti/vxlib/vxlib.h>

#define LEVEL_OF_FEEDBACK (0)   /* No printing of Output vectors */

extern void VXLIB_absDiff_i16s_i16s_o16s_d(uint8_t);
extern void VXLIB_absDiff_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_accumulateImage_i8u_io16s_d(uint8_t);
extern void VXLIB_accumulateSquareImage_i8u_io16s_d(uint8_t);
extern void VXLIB_accumulateWeightedImage_i8u_io8u_d(uint8_t);
extern void VXLIB_addSquare_i8u_i16s_o16s_d(uint8_t);
extern void VXLIB_addWeight_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_add_i16s_i16s_o16s_d(uint8_t);
extern void VXLIB_add_i8u_i16s_o16s_d(uint8_t);
extern void VXLIB_add_i8u_i8u_o16s_d(uint8_t);
extern void VXLIB_add_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_and_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_box_3x3_i8u_o8u_d(uint8_t);
extern void VXLIB_cannyNMS_i16s_i16s_i16u_o8u_d(uint8_t);
extern void VXLIB_channelCombine_2to1_i8u_o8u_d(uint8_t);
extern void VXLIB_channelCombine_3to1_i8u_o8u_d(uint8_t);
extern void VXLIB_channelCombine_4to1_i8u_o8u_d(uint8_t);
extern void VXLIB_channelCombine_yuyv_i8u_o8u_d(uint8_t);
extern void VXLIB_channelCopy_1to1_i8u_o8u_d(uint8_t);
extern void VXLIB_channelExtract_1of2_i8u_o8u_d(uint8_t);
extern void VXLIB_channelExtract_1of3_i8u_o8u_d(uint8_t);
extern void VXLIB_channelExtract_1of4_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBtoNV12_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_d(uint8_t);
extern void VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_d(uint8_t);
extern void VXLIB_convertDepth_i16s_o8u_d(uint8_t);
extern void VXLIB_convertDepth_i8u_o16s_d(uint8_t);
extern void VXLIB_convolve_3x3_i8u_c16s_o16s_d(uint8_t);
extern void VXLIB_convolve_3x3_i8u_c16s_o8u_d(uint8_t);
extern void VXLIB_convolve_5x5_i8u_c16s_o16s_d(uint8_t);
extern void VXLIB_convolve_5x5_i8u_c16s_o8u_d(uint8_t);
extern void VXLIB_convolve_7x7_i8u_c16s_o16s_d(uint8_t);
extern void VXLIB_convolve_7x7_i8u_c16s_o8u_d(uint8_t);
extern void VXLIB_convolve_i8u_c16s_o16s_d(uint8_t);
extern void VXLIB_convolve_i8u_c16s_o8u_d(uint8_t);
extern void VXLIB_dilate_3x3_i8u_o8u_d(uint8_t);
extern void VXLIB_dilate_MxN_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_doubleThreshold_i16u_i8u_d(uint8_t);
extern void VXLIB_edgeTracing_i8u_d(uint8_t);
extern void VXLIB_equalizeHist_i8u_o8u_d(uint8_t);
extern void VXLIB_erode_3x3_i8u_o8u_d(uint8_t);
extern void VXLIB_erode_MxN_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_fastCornersDetect_i8u_d(uint8_t);
extern void VXLIB_fastCornersNMS_i8u_d(uint8_t);
extern void VXLIB_fastCornersScore_i8u_d(uint8_t);
extern void VXLIB_fastCorners_i8u_d(uint8_t);
extern void VXLIB_gaussian_3x3_i8u_o8u_d(uint8_t);
extern void VXLIB_gaussian_5x5_br_i8u_o8u_d(uint8_t);
extern void VXLIB_gaussian_5x5_i8u_o8u_d(uint8_t);
extern void VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_d(uint8_t);
extern void VXLIB_halfScaleGaussian_5x5_i8u_o8u_d(uint8_t);
extern void VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_d(uint8_t);
extern void VXLIB_harrisCornersDetect_i32f_d(uint8_t);
extern void VXLIB_harrisCornersNMS_i32f_d(uint8_t);
extern void VXLIB_harrisCornersScore_i16s_i16s_o32f_d(uint8_t);
extern void VXLIB_harrisCornersScore_i32s_i32s_o32f_d(uint8_t);
extern void VXLIB_histogramCdfLut_i32u_o8u_d(uint8_t);
extern void VXLIB_histogramSimple_i8u_o32u_d(uint8_t);
extern void VXLIB_histogram_i8u_o32u_d(uint8_t);
extern void VXLIB_integralImage_i8u_o32u_d(uint8_t);
extern void VXLIB_magnitude_i16s_i16s_o16s_d(uint8_t);
extern void VXLIB_meanStdDev_i8u_o32f_d(uint8_t);
extern void VXLIB_median_3x3_i8u_o8u_d(uint8_t);
extern void VXLIB_median_MxN_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_minMaxLoc_i16s_d(uint8_t);
extern void VXLIB_minMaxLoc_i8u_d(uint8_t);
extern void VXLIB_multiply_i16s_i16s_o16s_d(uint8_t);
extern void VXLIB_multiply_i8u_i16s_o16s_d(uint8_t);
extern void VXLIB_multiply_i8u_i8u_o16s_d(uint8_t);
extern void VXLIB_multiply_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_normL1_i16s_i16s_o16u_d(uint8_t);
extern void VXLIB_normL2_i16s_i16s_o16u_d(uint8_t);
extern void VXLIB_not_i8u_o8u_d(uint8_t);
extern void VXLIB_or_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_phase_i16s_i16s_o8u_d(uint8_t);
extern void VXLIB_remapBilinear_bc_i8u_i32f_o8u_d(uint8_t);
extern void VXLIB_remapNearest_bc_i8u_i32f_o8u_d(uint8_t);
extern void VXLIB_scaleImageBilinear_bc_i8u_o8u_d(uint8_t);
extern void VXLIB_scaleImageBilinear_br_i8u_o8u_d(uint8_t);
extern void VXLIB_scaleImageBilinear_i8u_o8u_d(uint8_t);
extern void VXLIB_scaleImageNearest_i8u_o8u_d(uint8_t);
extern void VXLIB_scharr_3x3_i8u_o16s_o16s_d(uint8_t);
extern void VXLIB_sobelX_3x3_i8u_o16s_d(uint8_t);
extern void VXLIB_sobelY_3x3_i8u_o16s_d(uint8_t);
extern void VXLIB_sobel_3x3_i8u_o16s_o16s_d(uint8_t);
extern void VXLIB_sobel_5x5_i8u_o16s_o16s_d(uint8_t);
extern void VXLIB_sobel_7x7_i8u_o16s_o16s_d(uint8_t);
extern void VXLIB_sobel_7x7_i8u_o32s_o32s_d(uint8_t);
extern void VXLIB_subtract_i16s_i16s_o16s_d(uint8_t);
extern void VXLIB_subtract_i8u_i16s_o16s_d(uint8_t);
extern void VXLIB_subtract_i8u_i8u_o16s_d(uint8_t);
extern void VXLIB_subtract_i8u_i8u_o8u_d(uint8_t);
extern void VXLIB_tableLookup_i16s_o16s_d(uint8_t);
extern void VXLIB_tableLookup_i8u_o8u_d(uint8_t);
extern void VXLIB_thresholdBinary_i8u_o8u_d(uint8_t);
extern void VXLIB_thresholdRange_i8u_o8u_d(uint8_t);
extern void VXLIB_trackFeaturesLK_i8u_d(uint8_t);
extern void VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpAffineBilinear_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpAffineNearest_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_d(uint8_t);
extern void VXLIB_xor_i8u_i8u_o8u_d(uint8_t);


void main()
{
  TI_cache_init();

  	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_absDiff_i16s_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_absDiff_i16s_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_absDiff_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_absDiff_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_accumulateImage_i8u_io16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_accumulateImage_i8u_io16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_accumulateSquareImage_i8u_io16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_accumulateSquareImage_i8u_io16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_accumulateWeightedImage_i8u_io8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_accumulateWeightedImage_i8u_io8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_addSquare_i8u_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_addSquare_i8u_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_addWeight_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_addWeight_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_add_i16s_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_add_i16s_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_add_i8u_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_add_i8u_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_add_i8u_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_add_i8u_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_add_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_add_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_and_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_and_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_box_3x3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_box_3x3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_cannyNMS_i16s_i16s_i16u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_cannyNMS_i16s_i16s_i16u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelCombine_2to1_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelCombine_2to1_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelCombine_3to1_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelCombine_3to1_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelCombine_4to1_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelCombine_4to1_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelCombine_yuyv_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelCombine_yuyv_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelCopy_1to1_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelCopy_1to1_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelExtract_1of2_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelExtract_1of2_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelExtract_1of3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelExtract_1of3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_channelExtract_1of4_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_channelExtract_1of4_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_IYUVtoNV12_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_IYUVtoRGB_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_NVXXtoRGB_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBtoIYUV_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBtoNV12_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBtoNV12_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBtoRGBX_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBtoYUV4_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBXtoNV12_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBXtoRGB_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_YUVXtoNV12_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_colorConvert_YUVXtoRGB_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convertDepth_i16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convertDepth_i16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convertDepth_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convertDepth_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_3x3_i8u_c16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_3x3_i8u_c16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_3x3_i8u_c16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_3x3_i8u_c16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_5x5_i8u_c16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_5x5_i8u_c16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_5x5_i8u_c16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_5x5_i8u_c16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_7x7_i8u_c16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_7x7_i8u_c16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_7x7_i8u_c16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_7x7_i8u_c16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_i8u_c16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_i8u_c16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_convolve_i8u_c16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_convolve_i8u_c16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_dilate_3x3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_dilate_3x3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_dilate_MxN_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_dilate_MxN_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_doubleThreshold_i16u_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_doubleThreshold_i16u_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_edgeTracing_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_edgeTracing_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_equalizeHist_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_equalizeHist_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_erode_3x3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_erode_3x3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_erode_MxN_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_erode_MxN_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_fastCornersDetect_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_fastCornersDetect_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_fastCornersNMS_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_fastCornersNMS_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_fastCornersScore_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_fastCornersScore_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_fastCorners_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_fastCorners_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_gaussian_3x3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_gaussian_3x3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_gaussian_5x5_br_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_gaussian_5x5_br_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_gaussian_5x5_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_gaussian_5x5_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_halfScaleGaussian_5x5_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_halfScaleGaussian_5x5_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_harrisCornersDetect_i32f     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_harrisCornersDetect_i32f_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_harrisCornersNMS_i32f     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_harrisCornersNMS_i32f_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_harrisCornersScore_i16s_i16s_o32f     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_harrisCornersScore_i16s_i16s_o32f_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_harrisCornersScore_i32s_i32s_o32f     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_harrisCornersScore_i32s_i32s_o32f_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_histogramCdfLut_i32u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_histogramCdfLut_i32u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_histogramSimple_i8u_o32u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_histogramSimple_i8u_o32u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_histogram_i8u_o32u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_histogram_i8u_o32u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_integralImage_i8u_o32u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_integralImage_i8u_o32u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_magnitude_i16s_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_magnitude_i16s_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_meanStdDev_i8u_o32f     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_meanStdDev_i8u_o32f_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_median_3x3_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_median_3x3_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_median_MxN_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_median_MxN_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_minMaxLoc_i16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_minMaxLoc_i16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_minMaxLoc_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_minMaxLoc_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_multiply_i16s_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_multiply_i16s_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_multiply_i8u_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_multiply_i8u_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_multiply_i8u_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_multiply_i8u_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_multiply_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_multiply_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_normL1_i16s_i16s_o16u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_normL1_i16s_i16s_o16u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_normL2_i16s_i16s_o16u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_normL2_i16s_i16s_o16u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_not_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_not_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_or_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_or_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_phase_i16s_i16s_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_phase_i16s_i16s_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_remapBilinear_bc_i8u_i32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_remapBilinear_bc_i8u_i32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_remapNearest_bc_i8u_i32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_remapNearest_bc_i8u_i32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_scaleImageBilinear_bc_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_scaleImageBilinear_bc_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_scaleImageBilinear_br_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_scaleImageBilinear_br_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_scaleImageBilinear_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_scaleImageBilinear_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_scaleImageNearest_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_scaleImageNearest_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_scharr_3x3_i8u_o16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_scharr_3x3_i8u_o16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobelX_3x3_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobelX_3x3_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobelY_3x3_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobelY_3x3_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobel_3x3_i8u_o16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobel_3x3_i8u_o16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobel_5x5_i8u_o16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobel_5x5_i8u_o16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobel_7x7_i8u_o16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobel_7x7_i8u_o16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_sobel_7x7_i8u_o32s_o32s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_sobel_7x7_i8u_o32s_o32s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_subtract_i16s_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_subtract_i16s_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_subtract_i8u_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_subtract_i8u_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_subtract_i8u_i8u_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_subtract_i8u_i8u_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_subtract_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_subtract_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_tableLookup_i16s_o16s     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_tableLookup_i16s_o16s_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_tableLookup_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_tableLookup_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_thresholdBinary_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_thresholdBinary_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_thresholdRange_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_thresholdRange_i8u_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_trackFeaturesLK_i8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_trackFeaturesLK_i8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpAffineBilinear_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpAffineBilinear_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpAffineNearest_bc_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpAffineNearest_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpAffineNearest_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_warpPerspectiveNearest_i8u_c32f_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_d(LEVEL_OF_FEEDBACK);

	printf("\n\n");
	printf(" +---------------------------------------+\n");
	printf(" | TESTING: VXLIB_xor_i8u_i8u_o8u     |\n");
	printf(" +---------------------------------------+\n\n");
	VXLIB_xor_i8u_i8u_o8u_d(LEVEL_OF_FEEDBACK);


}
