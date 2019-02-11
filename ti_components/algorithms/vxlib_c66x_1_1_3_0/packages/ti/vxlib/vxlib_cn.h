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
**|        Copyright (c) 2016 - 2018 Texas Instruments Incorporated          |**
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

#include <ti/vxlib/src/vx/VXLIB_absDiff_i16s_i16s_o16s/VXLIB_absDiff_i16s_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_absDiff_i8u_i8u_o8u/VXLIB_absDiff_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_accumulateImage_i8u_io16s/VXLIB_accumulateImage_i8u_io16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_accumulateSquareImage_i8u_io16s/VXLIB_accumulateSquareImage_i8u_io16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_accumulateWeightedImage_i8u_io8u/VXLIB_accumulateWeightedImage_i8u_io8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_addSquare_i8u_i16s_o16s/VXLIB_addSquare_i8u_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_addWeight_i8u_i8u_o8u/VXLIB_addWeight_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_add_i16s_i16s_o16s/VXLIB_add_i16s_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_add_i8u_i16s_o16s/VXLIB_add_i8u_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o16s/VXLIB_add_i8u_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_add_i8u_i8u_o8u/VXLIB_add_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_and_i8u_i8u_o8u/VXLIB_and_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_box_3x3_i8u_o8u/VXLIB_box_3x3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelCombine_2to1_i8u_o8u/VXLIB_channelCombine_2to1_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelCombine_3to1_i8u_o8u/VXLIB_channelCombine_3to1_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelCombine_4to1_i8u_o8u/VXLIB_channelCombine_4to1_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelCombine_yuyv_i8u_o8u/VXLIB_channelCombine_yuyv_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelCopy_1to1_i8u_o8u/VXLIB_channelCopy_1to1_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelExtract_1of2_i8u_o8u/VXLIB_channelExtract_1of2_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelExtract_1of3_i8u_o8u/VXLIB_channelExtract_1of3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_channelExtract_1of4_i8u_o8u/VXLIB_channelExtract_1of4_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convertDepth_i16s_o8u/VXLIB_convertDepth_i16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convertDepth_i8u_o16s/VXLIB_convertDepth_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s/VXLIB_convolve_3x3_i8u_c16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u/VXLIB_convolve_3x3_i8u_c16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s/VXLIB_convolve_5x5_i8u_c16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u/VXLIB_convolve_5x5_i8u_c16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s/VXLIB_convolve_7x7_i8u_c16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u/VXLIB_convolve_7x7_i8u_c16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o16s/VXLIB_convolve_i8u_c16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_convolve_i8u_c16s_o8u/VXLIB_convolve_i8u_c16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_dilate_3x3_i8u_o8u/VXLIB_dilate_3x3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u/VXLIB_dilate_MxN_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_doubleThreshold_i16u_i8u/VXLIB_doubleThreshold_i16u_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_edgeTracing_i8u/VXLIB_edgeTracing_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_equalizeHist_i8u_o8u/VXLIB_equalizeHist_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_erode_3x3_i8u_o8u/VXLIB_erode_3x3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_erode_MxN_i8u_i8u_o8u/VXLIB_erode_MxN_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_fastCornersDetect_i8u/VXLIB_fastCornersDetect_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_fastCornersNMS_i8u/VXLIB_fastCornersNMS_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_fastCornersScore_i8u/VXLIB_fastCornersScore_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_fastCorners_i8u/VXLIB_fastCorners_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_gaussian_3x3_i8u_o8u/VXLIB_gaussian_3x3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_gaussian_5x5_br_i8u_o8u/VXLIB_gaussian_5x5_br_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_gaussian_5x5_i8u_o8u/VXLIB_gaussian_5x5_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u/VXLIB_halfScaleGaussian_5x5_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_harrisCornersDetect_i32f/VXLIB_harrisCornersDetect_i32f_cn.h>
#include <ti/vxlib/src/vx/VXLIB_harrisCornersNMS_i32f/VXLIB_harrisCornersNMS_i32f_cn.h>
#include <ti/vxlib/src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f/VXLIB_harrisCornersScore_i16s_i16s_o32f_cn.h>
#include <ti/vxlib/src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f/VXLIB_harrisCornersScore_i32s_i32s_o32f_cn.h>
#include <ti/vxlib/src/vx/VXLIB_histogramCdfLut_i32u_o8u/VXLIB_histogramCdfLut_i32u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_histogramSimple_i8u_o32u/VXLIB_histogramSimple_i8u_o32u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_histogram_i8u_o32u/VXLIB_histogram_i8u_o32u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_integralImage_i8u_o32u/VXLIB_integralImage_i8u_o32u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_magnitude_i16s_i16s_o16s/VXLIB_magnitude_i16s_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_meanStdDev_i8u_o32f/VXLIB_meanStdDev_i8u_o32f_cn.h>
#include <ti/vxlib/src/vx/VXLIB_median_3x3_i8u_o8u/VXLIB_median_3x3_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_median_MxN_i8u_i8u_o8u/VXLIB_median_MxN_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_minMaxLoc_i16s/VXLIB_minMaxLoc_i16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_minMaxLoc_i8u/VXLIB_minMaxLoc_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_multiply_i16s_i16s_o16s/VXLIB_multiply_i16s_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_multiply_i8u_i16s_o16s/VXLIB_multiply_i8u_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o16s/VXLIB_multiply_i8u_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_multiply_i8u_i8u_o8u/VXLIB_multiply_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_normL1_i16s_i16s_o16u/VXLIB_normL1_i16s_i16s_o16u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_normL2_i16s_i16s_o16u/VXLIB_normL2_i16s_i16s_o16u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_not_i8u_o8u/VXLIB_not_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_or_i8u_i8u_o8u/VXLIB_or_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_phase_i16s_i16s_o8u/VXLIB_phase_i16s_i16s_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u/VXLIB_remapBilinear_bc_i8u_i32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u/VXLIB_remapNearest_bc_i8u_i32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u/VXLIB_scaleImageBilinear_bc_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u/VXLIB_scaleImageBilinear_br_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_scaleImageBilinear_i8u_o8u/VXLIB_scaleImageBilinear_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_scaleImageNearest_i8u_o8u/VXLIB_scaleImageNearest_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s/VXLIB_scharr_3x3_i8u_o16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobelX_3x3_i8u_o16s/VXLIB_sobelX_3x3_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobelY_3x3_i8u_o16s/VXLIB_sobelY_3x3_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s/VXLIB_sobel_3x3_i8u_o16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s/VXLIB_sobel_5x5_i8u_o16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s/VXLIB_sobel_7x7_i8u_o16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s/VXLIB_sobel_7x7_i8u_o32s_o32s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_subtract_i16s_i16s_o16s/VXLIB_subtract_i16s_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_subtract_i8u_i16s_o16s/VXLIB_subtract_i8u_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o16s/VXLIB_subtract_i8u_i8u_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_subtract_i8u_i8u_o8u/VXLIB_subtract_i8u_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_tableLookup_i16s_o16s/VXLIB_tableLookup_i16s_o16s_cn.h>
#include <ti/vxlib/src/vx/VXLIB_tableLookup_i8u_o8u/VXLIB_tableLookup_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_thresholdBinary_i8u_o8u/VXLIB_thresholdBinary_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_thresholdRange_i8u_o8u/VXLIB_thresholdRange_i8u_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_trackFeaturesLK_i8u/VXLIB_trackFeaturesLK_i8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u/VXLIB_warpAffineBilinear_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u/VXLIB_warpAffineNearest_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_cn.h>
#include <ti/vxlib/src/vx/VXLIB_xor_i8u_i8u_o8u/VXLIB_xor_i8u_i8u_o8u_cn.h>

#ifdef __cplusplus
}
#endif /* __cplusplus */

