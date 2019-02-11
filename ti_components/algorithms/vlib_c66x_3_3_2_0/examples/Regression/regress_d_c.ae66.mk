#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: Regression/regress_d_c.ae66.mk
#*
#* DESCRIPTION: Defines Source Files, Compilers flags and build rules
#*
#*
#* This is an auto-generated file          
#*******************************************************************************
#

#
# Macro definitions referenced below
#
empty =
space =$(empty) $(empty)
CC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
AC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
ARIN = "$(C6X_GEN_INSTALL_DIR)/bin/"ar6x 
LIBINFO = "$(C6X_GEN_INSTALL_DIR)/bin/libinfo6x"
LD = "$(C6X_GEN_INSTALL_DIR)/bin/"lnk6x --abi=eabi 
CGINCS = $(strip $(subst $(space),\$(space),$(C6X_GEN_INSTALL_DIR)/include))
RTSLIB = -l "$(C6X_GEN_INSTALL_DIR)/lib/undefined"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = oe66
AOBJEXT = se66
INTERNALDEFS =  -Dti_targets_elf_C66 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep 
INTERNALLINKDEFS =  -o $@ -m $@.map
OBJDIR = ./package/lib/Regression/regress_d_c


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  OPTFLAGS = -g
else
  OPTFLAGS = -o3 --symdebug:none
endif



#List the commontestsrc Files
COMMONTESTSRCC= \
    ./../packages/ti/vlib/src/VLIB_afast12_detectCorners/VLIB_afast12_detectCorners_d.c\
    ./../packages/ti/vlib/src/VLIB_afast12_detectCorners/VLIB_afast12_detectCorners_idat.c\
    ./../packages/ti/vlib/src/VLIB_afast9_detectCorners/VLIB_afast9_detectCorners_d.c\
    ./../packages/ti/vlib/src/VLIB_afast9_detectCorners/VLIB_afast9_detectCorners_idat.c\
    ./../packages/ti/vlib/src/VLIB_aFast_nonmaxSuppression/VLIB_aFast_nonmaxSuppression_d.c\
    ./../packages/ti/vlib/src/VLIB_aFast_nonmaxSuppression/VLIB_aFast_nonmaxSuppression_idat.c\
    ./../packages/ti/vlib/src/VLIB_bhattacharyaDistance_F32/VLIB_bhattacharyaDistance_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_bhattacharyaDistance_F32/VLIB_bhattacharyaDistance_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_bhattacharyaDistance_U32/VLIB_bhattacharyaDistance_U32_d.c\
    ./../packages/ti/vlib/src/VLIB_bhattacharyaDistance_U32/VLIB_bhattacharyaDistance_U32_idat.c\
    ./../packages/ti/vlib/src/VLIB_binarySkeleton/VLIB_binarySkeleton_d.c\
    ./../packages/ti/vlib/src/VLIB_binarySkeleton/VLIB_binarySkeleton_idat.c\
    ./../packages/ti/vlib/src/VLIB_blobAnalysis/VLIB_blobAnalysis_d.c\
    ./../packages/ti/vlib/src/VLIB_blobAnalysis/VLIB_blobAnalysis_idat.c\
    ./../packages/ti/vlib/src/VLIB_blockMedian/VLIB_blockMedian_d.c\
    ./../packages/ti/vlib/src/VLIB_blockMedian/VLIB_blockMedian_idat.c\
    ./../packages/ti/vlib/src/VLIB_blockStatistics/VLIB_blockStatistics_d.c\
    ./../packages/ti/vlib/src/VLIB_blockStatistics/VLIB_blockStatistics_idat.c\
    ./../packages/ti/vlib/src/VLIB_Canny_Edge_Detection/VLIB_Canny_Edge_Detection_d.c\
    ./../packages/ti/vlib/src/VLIB_Canny_Edge_Detection/VLIB_Canny_Edge_Detection_idat.c\
    ./../packages/ti/vlib/src/VLIB_Connected_Components_Labeling/VLIB_Connected_Components_Labeling_d.c\
    ./../packages/ti/vlib/src/VLIB_Connected_Components_Labeling/VLIB_Connected_Components_Labeling_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_HSLpl/VLIB_convertUYVYint_to_HSLpl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_HSLpl/VLIB_convertUYVYint_to_HSLpl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_LABpl/VLIB_convertUYVYint_to_LABpl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_LABpl/VLIB_convertUYVYint_to_LABpl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_LABpl_LUT/VLIB_convertUYVYint_to_LABpl_LUT_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_LABpl_LUT/VLIB_convertUYVYint_to_LABpl_LUT_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_RGBpl/VLIB_convertUYVYint_to_RGBpl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_RGBpl/VLIB_convertUYVYint_to_RGBpl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV420pl/VLIB_convertUYVYint_to_YUV420pl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV420pl/VLIB_convertUYVYint_to_YUV420pl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV422pl/VLIB_convertUYVYint_to_YUV422pl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV422pl/VLIB_convertUYVYint_to_YUV422pl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV444pl/VLIB_convertUYVYint_to_YUV444pl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYint_to_YUV444pl/VLIB_convertUYVYint_to_YUV444pl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYpl_to_YUVint/VLIB_convertUYVYpl_to_YUVint_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYpl_to_YUVint/VLIB_convertUYVYpl_to_YUVint_idat.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYsemipl_to_YUVpl/VLIB_convertUYVYsemipl_to_YUVpl_d.c\
    ./../packages/ti/vlib/src/VLIB_convertUYVYsemipl_to_YUVpl/VLIB_convertUYVYsemipl_to_YUVpl_idat.c\
    ./../packages/ti/vlib/src/VLIB_convert_NV12_to_RGBpl_tile/VLIB_convert_NV12_to_RGBpl_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_convert_NV12_to_RGBpl_tile/VLIB_convert_NV12_to_RGBpl_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile/VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_coOccurrenceMatrix/VLIB_coOccurrenceMatrix_d.c\
    ./../packages/ti/vlib/src/VLIB_coOccurrenceMatrix/VLIB_coOccurrenceMatrix_idat.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_cross/VLIB_dilate_bin_cross_d.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_cross/VLIB_dilate_bin_cross_idat.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_mask/VLIB_dilate_bin_mask_d.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_mask/VLIB_dilate_bin_mask_idat.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_square/VLIB_dilate_bin_square_d.c\
    ./../packages/ti/vlib/src/VLIB_dilate_bin_square/VLIB_dilate_bin_square_idat.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD16/VLIB_disparity_SAD16_d.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD16/VLIB_disparity_SAD16_idat.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD8/VLIB_disparity_SAD8_d.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD8/VLIB_disparity_SAD8_idat.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD_firstRow16/VLIB_disparity_SAD_firstRow16_d.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD_firstRow16/VLIB_disparity_SAD_firstRow16_idat.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD_firstRow8/VLIB_disparity_SAD_firstRow8_d.c\
    ./../packages/ti/vlib/src/VLIB_disparity_SAD_firstRow8/VLIB_disparity_SAD_firstRow8_idat.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_cross/VLIB_erode_bin_cross_d.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_cross/VLIB_erode_bin_cross_idat.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_mask/VLIB_erode_bin_mask_d.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_mask/VLIB_erode_bin_mask_idat.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_singlePixel/VLIB_erode_bin_singlePixel_d.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_singlePixel/VLIB_erode_bin_singlePixel_idat.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_square/VLIB_erode_bin_square_d.c\
    ./../packages/ti/vlib/src/VLIB_erode_bin_square/VLIB_erode_bin_square_idat.c\
    ./../packages/ti/vlib/src/VLIB_extract8bitBackgroundS16/VLIB_extract8bitBackgroundS16_d.c\
    ./../packages/ti/vlib/src/VLIB_extract8bitBackgroundS16/VLIB_extract8bitBackgroundS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_extractLumaFromUYUV/VLIB_extractLumaFromUYUV_d.c\
    ./../packages/ti/vlib/src/VLIB_extractLumaFromUYUV/VLIB_extractLumaFromUYUV_idat.c\
    ./../packages/ti/vlib/src/VLIB_extractLumaFromYUYV/VLIB_extractLumaFromYUYV_d.c\
    ./../packages/ti/vlib/src/VLIB_extractLumaFromYUYV/VLIB_extractLumaFromYUYV_idat.c\
    ./../packages/ti/vlib/src/VLIB_findFundamentalMat/VLIB_findFundamentalMat_d.c\
    ./../packages/ti/vlib/src/VLIB_findFundamentalMat/VLIB_findFundamentalMat_idat.c\
    ./../packages/ti/vlib/src/VLIB_gauss5x5PyramidKernel_16/VLIB_gauss5x5PyramidKernel_16_d.c\
    ./../packages/ti/vlib/src/VLIB_gauss5x5PyramidKernel_16/VLIB_gauss5x5PyramidKernel_16_idat.c\
    ./../packages/ti/vlib/src/VLIB_gauss5x5PyramidKernel_8/VLIB_gauss5x5PyramidKernel_8_d.c\
    ./../packages/ti/vlib/src/VLIB_gauss5x5PyramidKernel_8/VLIB_gauss5x5PyramidKernel_8_idat.c\
    ./../packages/ti/vlib/src/VLIB_goodFeaturestoTrack/VLIB_goodFeaturestoTrack_d.c\
    ./../packages/ti/vlib/src/VLIB_goodFeaturestoTrack/VLIB_goodFeaturestoTrack_idat.c\
    ./../packages/ti/vlib/src/VLIB_gradientH5x5PyramidKernel_8/VLIB_gradientH5x5PyramidKernel_8_d.c\
    ./../packages/ti/vlib/src/VLIB_gradientH5x5PyramidKernel_8/VLIB_gradientH5x5PyramidKernel_8_idat.c\
    ./../packages/ti/vlib/src/VLIB_gradientV5x5PyramidKernel_8/VLIB_gradientV5x5PyramidKernel_8_d.c\
    ./../packages/ti/vlib/src/VLIB_gradientV5x5PyramidKernel_8/VLIB_gradientV5x5PyramidKernel_8_idat.c\
    ./../packages/ti/vlib/src/VLIB_grayscale_morphology/VLIB_grayscale_morphology_d.c\
    ./../packages/ti/vlib/src/VLIB_grayscale_morphology/VLIB_grayscale_morphology_idat.c\
    ./../packages/ti/vlib/src/VLIB_haarDetectObjectsDense/VLIB_haarDetectObjectsDense_d.c\
    ./../packages/ti/vlib/src/VLIB_haarDetectObjectsDense/VLIB_haarDetectObjectsDense_idat.c\
    ./../packages/ti/vlib/src/VLIB_haarDetectObjectsSparse/VLIB_haarDetectObjectsSparse_d.c\
    ./../packages/ti/vlib/src/VLIB_haarDetectObjectsSparse/VLIB_haarDetectObjectsSparse_idat.c\
    ./../packages/ti/vlib/src/VLIB_hammingDistance/VLIB_hammingDistance_d.c\
    ./../packages/ti/vlib/src/VLIB_hammingDistance/VLIB_hammingDistance_idat.c\
    ./../packages/ti/vlib/src/VLIB_harrisScore_7x7/VLIB_harrisScore_7x7_d.c\
    ./../packages/ti/vlib/src/VLIB_harrisScore_7x7/VLIB_harrisScore_7x7_idat.c\
    ./../packages/ti/vlib/src/VLIB_harrisScore_7x7_S32/VLIB_harrisScore_7x7_S32_d.c\
    ./../packages/ti/vlib/src/VLIB_harrisScore_7x7_S32/VLIB_harrisScore_7x7_S32_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_Init_U16/VLIB_histogram_1D_Init_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_Init_U16/VLIB_histogram_1D_Init_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_Init_U8/VLIB_histogram_1D_Init_U8_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_Init_U8/VLIB_histogram_1D_Init_U8_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_U16/VLIB_histogram_1D_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_U16/VLIB_histogram_1D_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_U8/VLIB_histogram_1D_U8_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_1D_U8/VLIB_histogram_1D_U8_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_equal_8/VLIB_histogram_equal_8_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_equal_8/VLIB_histogram_equal_8_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_equal_8_f32/VLIB_histogram_equal_8_f32_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_equal_8_f32/VLIB_histogram_equal_8_f32_idat.c\
    ./../packages/ti/vlib/src/VLIB_histogram_nD_U16/VLIB_histogram_nD_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_histogram_nD_U16/VLIB_histogram_nD_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_homographyDecomposition/VLIB_homographyDecomposition_d.c\
    ./../packages/ti/vlib/src/VLIB_homographyDecomposition/VLIB_homographyDecomposition_idat.c\
    ./../packages/ti/vlib/src/VLIB_houghLineFromList/VLIB_houghLineFromList_d.c\
    ./../packages/ti/vlib/src/VLIB_houghLineFromList/VLIB_houghLineFromList_idat.c\
    ./../packages/ti/vlib/src/VLIB_hysteresisThresholding/VLIB_hysteresisThresholding_d.c\
    ./../packages/ti/vlib/src/VLIB_hysteresisThresholding/VLIB_hysteresisThresholding_idat.c\
    ./../packages/ti/vlib/src/VLIB_imagePyramid16/VLIB_imagePyramid16_d.c\
    ./../packages/ti/vlib/src/VLIB_imagePyramid16/VLIB_imagePyramid16_idat.c\
    ./../packages/ti/vlib/src/VLIB_imagePyramid8/VLIB_imagePyramid8_d.c\
    ./../packages/ti/vlib/src/VLIB_imagePyramid8/VLIB_imagePyramid8_idat.c\
    ./../packages/ti/vlib/src/VLIB_image_rescale/VLIB_image_rescale_d.c\
    ./../packages/ti/vlib/src/VLIB_image_rescale/VLIB_image_rescale_idat.c\
    ./../packages/ti/vlib/src/VLIB_initMeanWithLumaS16/VLIB_initMeanWithLumaS16_d.c\
    ./../packages/ti/vlib/src/VLIB_initMeanWithLumaS16/VLIB_initMeanWithLumaS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_initMeanWithLumaS32/VLIB_initMeanWithLumaS32_d.c\
    ./../packages/ti/vlib/src/VLIB_initMeanWithLumaS32/VLIB_initMeanWithLumaS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_initUYVYint_to_LABpl_LUT/VLIB_initUYVYint_to_LABpl_LUT_d.c\
    ./../packages/ti/vlib/src/VLIB_initUYVYint_to_LABpl_LUT/VLIB_initUYVYint_to_LABpl_LUT_idat.c\
    ./../packages/ti/vlib/src/VLIB_initVarWithConstS16/VLIB_initVarWithConstS16_d.c\
    ./../packages/ti/vlib/src/VLIB_initVarWithConstS16/VLIB_initVarWithConstS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_initVarWithConstS32/VLIB_initVarWithConstS32_d.c\
    ./../packages/ti/vlib/src/VLIB_initVarWithConstS32/VLIB_initVarWithConstS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_insertLumaIntoYUYV/VLIB_insertLumaIntoYUYV_d.c\
    ./../packages/ti/vlib/src/VLIB_insertLumaIntoYUYV/VLIB_insertLumaIntoYUYV_idat.c\
    ./../packages/ti/vlib/src/VLIB_integralImage16/VLIB_integralImage16_d.c\
    ./../packages/ti/vlib/src/VLIB_integralImage16/VLIB_integralImage16_idat.c\
    ./../packages/ti/vlib/src/VLIB_integralImage8/VLIB_integralImage8_d.c\
    ./../packages/ti/vlib/src/VLIB_integralImage8/VLIB_integralImage8_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_1x2_Correct_F32/VLIB_kalmanFilter_1x2_Correct_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_1x2_Correct_F32/VLIB_kalmanFilter_1x2_Correct_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_1x2_Predict_F32/VLIB_kalmanFilter_1x2_Predict_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_1x2_Predict_F32/VLIB_kalmanFilter_1x2_Predict_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct/VLIB_kalmanFilter_2x4_Correct_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct/VLIB_kalmanFilter_2x4_Correct_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_F32/VLIB_kalmanFilter_2x4_Correct_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_F32/VLIB_kalmanFilter_2x4_Correct_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_S16_F32/VLIB_kalmanFilter_2x4_Correct_S16_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Correct_S16_F32/VLIB_kalmanFilter_2x4_Correct_S16_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict/VLIB_kalmanFilter_2x4_Predict_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict/VLIB_kalmanFilter_2x4_Predict_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_F32/VLIB_kalmanFilter_2x4_Predict_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_F32/VLIB_kalmanFilter_2x4_Predict_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_S16_F32/VLIB_kalmanFilter_2x4_Predict_S16_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_2x4_Predict_S16_F32/VLIB_kalmanFilter_2x4_Predict_S16_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x12_Correct_F32/VLIB_kalmanFilter_4x12_Correct_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x12_Correct_F32/VLIB_kalmanFilter_4x12_Correct_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x12_Predict_F32/VLIB_kalmanFilter_4x12_Predict_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x12_Predict_F32/VLIB_kalmanFilter_4x12_Predict_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct/VLIB_kalmanFilter_4x6_Correct_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct/VLIB_kalmanFilter_4x6_Correct_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_F32/VLIB_kalmanFilter_4x6_Correct_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_F32/VLIB_kalmanFilter_4x6_Correct_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_S16_F32/VLIB_kalmanFilter_4x6_Correct_S16_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Correct_S16_F32/VLIB_kalmanFilter_4x6_Correct_S16_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict/VLIB_kalmanFilter_4x6_Predict_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict/VLIB_kalmanFilter_4x6_Predict_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_F32/VLIB_kalmanFilter_4x6_Predict_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_F32/VLIB_kalmanFilter_4x6_Predict_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_S16_F32/VLIB_kalmanFilter_4x6_Predict_S16_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x6_Predict_S16_F32/VLIB_kalmanFilter_4x6_Predict_S16_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x8_Correct_F32/VLIB_kalmanFilter_4x8_Correct_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x8_Correct_F32/VLIB_kalmanFilter_4x8_Correct_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x8_Predict_F32/VLIB_kalmanFilter_4x8_Predict_F32_d.c\
    ./../packages/ti/vlib/src/VLIB_kalmanFilter_4x8_Predict_F32/VLIB_kalmanFilter_4x8_Predict_F32_idat.c\
    ./../packages/ti/vlib/src/VLIB_L1DistanceS16/VLIB_L1DistanceS16_d.c\
    ./../packages/ti/vlib/src/VLIB_L1DistanceS16/VLIB_L1DistanceS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_f32/VLIB_L2_norm_f32_d.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_f32/VLIB_L2_norm_f32_idat.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i16/VLIB_L2_norm_i16_d.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i16/VLIB_L2_norm_i16_idat.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i32/VLIB_L2_norm_i32_d.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i32/VLIB_L2_norm_i32_idat.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i8/VLIB_L2_norm_i8_d.c\
    ./../packages/ti/vlib/src/VLIB_L2_norm_i8/VLIB_L2_norm_i8_idat.c\
    ./../packages/ti/vlib/src/VLIB_lbp/VLIB_lbp_d.c\
    ./../packages/ti/vlib/src/VLIB_lbp/VLIB_lbp_idat.c\
    ./../packages/ti/vlib/src/VLIB_legendreMoments/VLIB_legendreMoments_d.c\
    ./../packages/ti/vlib/src/VLIB_legendreMoments/VLIB_legendreMoments_idat.c\
    ./../packages/ti/vlib/src/VLIB_legendreMoments_Init/VLIB_legendreMoments_Init_d.c\
    ./../packages/ti/vlib/src/VLIB_legendreMoments_Init/VLIB_legendreMoments_Init_idat.c\
    ./../packages/ti/vlib/src/VLIB_matchTemplate/VLIB_matchTemplate_d.c\
    ./../packages/ti/vlib/src/VLIB_matchTemplate/VLIB_matchTemplate_idat.c\
    ./../packages/ti/vlib/src/VLIB_mixtureOfGaussiansS16/VLIB_mixtureOfGaussiansS16_d.c\
    ./../packages/ti/vlib/src/VLIB_mixtureOfGaussiansS16/VLIB_mixtureOfGaussiansS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_mixtureOfGaussiansS32/VLIB_mixtureOfGaussiansS32_d.c\
    ./../packages/ti/vlib/src/VLIB_mixtureOfGaussiansS32/VLIB_mixtureOfGaussiansS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_neuralNet_tile/VLIB_neuralNet_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_neuralNet_tile/VLIB_neuralNet_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_3x3_S16/VLIB_nonMaxSuppress_3x3_S16_d.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_3x3_S16/VLIB_nonMaxSuppress_3x3_S16_idat.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_5x5_S16/VLIB_nonMaxSuppress_5x5_S16_d.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_5x5_S16/VLIB_nonMaxSuppress_5x5_S16_idat.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_7x7_S16/VLIB_nonMaxSuppress_7x7_S16_d.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_7x7_S16/VLIB_nonMaxSuppress_7x7_S16_idat.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_U16/VLIB_nonMaxSuppress_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_U16/VLIB_nonMaxSuppress_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_U32/VLIB_nonMaxSuppress_U32_d.c\
    ./../packages/ti/vlib/src/VLIB_nonMaxSuppress_U32/VLIB_nonMaxSuppress_U32_idat.c\
    ./../packages/ti/vlib/src/VLIB_normalFlow_16/VLIB_normalFlow_16_d.c\
    ./../packages/ti/vlib/src/VLIB_normalFlow_16/VLIB_normalFlow_16_idat.c\
    ./../packages/ti/vlib/src/VLIB_normalize_input_i8u_o16s_tile/VLIB_normalize_input_i8u_o16s_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_normalize_input_i8u_o16s_tile/VLIB_normalize_input_i8u_o16s_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_ORB_bestFeaturesToFront/VLIB_ORB_bestFeaturesToFront_d.c\
    ./../packages/ti/vlib/src/VLIB_ORB_bestFeaturesToFront/VLIB_ORB_bestFeaturesToFront_idat.c\
    ./../packages/ti/vlib/src/VLIB_ORB_computeOrientation/VLIB_ORB_computeOrientation_d.c\
    ./../packages/ti/vlib/src/VLIB_ORB_computeOrientation/VLIB_ORB_computeOrientation_idat.c\
    ./../packages/ti/vlib/src/VLIB_ORB_computeRBrief/VLIB_ORB_computeRBrief_d.c\
    ./../packages/ti/vlib/src/VLIB_ORB_computeRBrief/VLIB_ORB_computeRBrief_idat.c\
    ./../packages/ti/vlib/src/VLIB_ORB_getHarrisScore/VLIB_ORB_getHarrisScore_d.c\
    ./../packages/ti/vlib/src/VLIB_ORB_getHarrisScore/VLIB_ORB_getHarrisScore_idat.c\
    ./../packages/ti/vlib/src/VLIB_originalfast12_detectCorners/VLIB_originalfast12_detectCorners_d.c\
    ./../packages/ti/vlib/src/VLIB_originalfast12_detectCorners/VLIB_originalfast12_detectCorners_idat.c\
    ./../packages/ti/vlib/src/VLIB_originalfast12_score/VLIB_originalfast12_score_d.c\
    ./../packages/ti/vlib/src/VLIB_originalfast12_score/VLIB_originalfast12_score_idat.c\
    ./../packages/ti/vlib/src/VLIB_originalfast9_detectCorners/VLIB_originalfast9_detectCorners_d.c\
    ./../packages/ti/vlib/src/VLIB_originalfast9_detectCorners/VLIB_originalfast9_detectCorners_idat.c\
    ./../packages/ti/vlib/src/VLIB_originalfast9_score/VLIB_originalfast9_score_d.c\
    ./../packages/ti/vlib/src/VLIB_originalfast9_score/VLIB_originalfast9_score_idat.c\
    ./../packages/ti/vlib/src/VLIB_packMask32/VLIB_packMask32_d.c\
    ./../packages/ti/vlib/src/VLIB_packMask32/VLIB_packMask32_idat.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterHoriz1stOrderS16/VLIB_recursiveFilterHoriz1stOrderS16_d.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterHoriz1stOrderS16/VLIB_recursiveFilterHoriz1stOrderS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterHoriz1stOrder/VLIB_recursiveFilterHoriz1stOrder_d.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterHoriz1stOrder/VLIB_recursiveFilterHoriz1stOrder_idat.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterVert1stOrderS16/VLIB_recursiveFilterVert1stOrderS16_d.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterVert1stOrderS16/VLIB_recursiveFilterVert1stOrderS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterVert1stOrder/VLIB_recursiveFilterVert1stOrder_d.c\
    ./../packages/ti/vlib/src/VLIB_recursiveFilterVert1stOrder/VLIB_recursiveFilterVert1stOrder_idat.c\
    ./../packages/ti/vlib/src/VLIB_ReLU_MaxPooling_2x2_skip2_tile/VLIB_ReLU_MaxPooling_2x2_skip2_tile_d.c\
    ./../packages/ti/vlib/src/VLIB_ReLU_MaxPooling_2x2_skip2_tile/VLIB_ReLU_MaxPooling_2x2_skip2_tile_idat.c\
    ./../packages/ti/vlib/src/VLIB_simplex_3D/VLIB_simplex_3D_d.c\
    ./../packages/ti/vlib/src/VLIB_simplex_3D/VLIB_simplex_3D_idat.c\
    ./../packages/ti/vlib/src/VLIB_simplex/VLIB_simplex_d.c\
    ./../packages/ti/vlib/src/VLIB_simplex/VLIB_simplex_idat.c\
    ./../packages/ti/vlib/src/VLIB_subtractBackgroundS16/VLIB_subtractBackgroundS16_d.c\
    ./../packages/ti/vlib/src/VLIB_subtractBackgroundS16/VLIB_subtractBackgroundS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_subtractBackgroundS32/VLIB_subtractBackgroundS32_d.c\
    ./../packages/ti/vlib/src/VLIB_subtractBackgroundS32/VLIB_subtractBackgroundS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_trackFeaturesLucasKanade_7x7/VLIB_trackFeaturesLucasKanade_7x7_d.c\
    ./../packages/ti/vlib/src/VLIB_trackFeaturesLucasKanade_7x7/VLIB_trackFeaturesLucasKanade_7x7_idat.c\
    ./../packages/ti/vlib/src/VLIB_triangulatePoints/VLIB_triangulatePoints_d.c\
    ./../packages/ti/vlib/src/VLIB_triangulatePoints/VLIB_triangulatePoints_idat.c\
    ./../packages/ti/vlib/src/VLIB_unpackMask32/VLIB_unpackMask32_d.c\
    ./../packages/ti/vlib/src/VLIB_unpackMask32/VLIB_unpackMask32_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRMeanS16/VLIB_updateEWRMeanS16_d.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRMeanS16/VLIB_updateEWRMeanS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRMeanS32/VLIB_updateEWRMeanS32_d.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRMeanS32/VLIB_updateEWRMeanS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRVarianceS16/VLIB_updateEWRVarianceS16_d.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRVarianceS16/VLIB_updateEWRVarianceS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRVarianceS32/VLIB_updateEWRVarianceS32_d.c\
    ./../packages/ti/vlib/src/VLIB_updateEWRVarianceS32/VLIB_updateEWRVarianceS32_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateUWRMeanS16/VLIB_updateUWRMeanS16_d.c\
    ./../packages/ti/vlib/src/VLIB_updateUWRMeanS16/VLIB_updateUWRMeanS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_updateUWRVarianceS16/VLIB_updateUWRVarianceS16_d.c\
    ./../packages/ti/vlib/src/VLIB_updateUWRVarianceS16/VLIB_updateUWRVarianceS16_idat.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_1D_U16/VLIB_weightedHistogram_1D_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_1D_U16/VLIB_weightedHistogram_1D_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_1D_U8/VLIB_weightedHistogram_1D_U8_d.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_1D_U8/VLIB_weightedHistogram_1D_U8_idat.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_nD_U16/VLIB_weightedHistogram_nD_U16_d.c\
    ./../packages/ti/vlib/src/VLIB_weightedHistogram_nD_U16/VLIB_weightedHistogram_nD_U16_idat.c\
    ./../packages/ti/vlib/src/VLIB_xyGradientsAndMagnitude/VLIB_xyGradientsAndMagnitude_d.c\
    ./../packages/ti/vlib/src/VLIB_xyGradientsAndMagnitude/VLIB_xyGradientsAndMagnitude_idat.c\
    ./../packages/ti/vlib/src/VLIB_xyGradients/VLIB_xyGradients_d.c\
    ./../packages/ti/vlib/src/VLIB_xyGradients/VLIB_xyGradients_idat.c\
    ./../packages/ti/vlib/src/VLIB_xyGradients_Magnitude_Orientations/VLIB_xyGradients_Magnitude_Orientations_d.c\
    ./../packages/ti/vlib/src/VLIB_xyGradients_Magnitude_Orientations/VLIB_xyGradients_Magnitude_Orientations_idat.c

# FLAGS for the commontestsrc Files
COMMONTESTSRCCFLAGS =  -c -k -q --mem_model:data=far -al -pds1111 -pds827 -pds824 -pds837 -pds1037 -pds195 -pdsw225 -pdsw994 -pdsw262 -pds77 -pden -pds232 -mw -os -g -mi10000 -as -ss -o3 --optimize_with_debug --mem_model:data=far -i../../../../packages -D__ONESHOTTEST

# Make Rule for the commontestsrc Files
COMMONTESTSRCCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(COMMONTESTSRCC))

$(COMMONTESTSRCCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cle66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(COMMONTESTSRCCFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(COMMONTESTSRCCOBJS):Regression\regress_d_c.ae66.mk
Regression\regress_d_c.ae66.mk:

#Include Depedency for commontestsrc Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(COMMONTESTSRCCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


Regression/regress_d_c.ae66 : $(COMMONTESTSRCCOBJS)
	@echo archiving $? into $@ ...
	@echo "rq $@ $?">$@.cmd
	$(ARIN) @$@.cmd
	if [ -f $(@D)/regress_d_c.lib  ]; then $(LIBINFO) -u -o=$(@D)/regress_d_c.lib $@; else $(LIBINFO) -o=$(@D)/regress_d_c.lib $@; fi;
