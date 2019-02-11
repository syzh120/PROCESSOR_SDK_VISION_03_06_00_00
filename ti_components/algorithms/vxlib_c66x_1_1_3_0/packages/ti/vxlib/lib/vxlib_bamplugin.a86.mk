#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/vxlib_bamplugin.a86.mk
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
CC = cl.exe -nologo -c -DWIN32 /EHsc /W3 /wd4068 /DWIN32_LEAN_AND_MEAN /D_CRT_SECURE_NO_DEPRECATE
AC = cl.exe -nologo -c
ARIN = lib.exe 
LD = link.exe 
CGINCS = $(strip $(subst $(space),\$(space),$(MSVC_GEN_INSTALL_DIR)/VC/include))
RTSLIB = -libpath:"$(MSVC_GEN_INSTALL_DIR)/VC/lib" -libpath:"$(MSVC_GEN_INSTALL_DIR)/Common7/IDE"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = o86
AOBJEXT = s86
INTERNALDEFS =  -Dmicrosoft_targets_VC98 -Dxdc_target_types__=microsoft/targets/std.h -Fo$@ 
INTERNALLINKDEFS =  -map:$@.map -pdb:$@.pdb -out:$@ 
OBJDIR = ./package/lib/lib/vxlib_bamplugina86


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  CC += /Od /MDd /Gm /Zi /RTC1
  INTERNALLINKDEFS += /DEBUG
else
  CC += /Ox /MD
endif


INTERNALLINKDEFS += /MACHINE:X86

#List the kernelBamc66Host Files
KERNELBAMC66HOSTC= \
    ./src/vx/VXLIB_absDiff_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_absDiff_i16s_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_absDiff_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_absDiff_i16s_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_absDiff_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_absDiff_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_absDiff_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_absDiff_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_add_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_add_i16s_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_add_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_add_i16s_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_add_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_add_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_add_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_add_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_add_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_add_i8u_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_add_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_add_i8u_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_add_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_add_i8u_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_add_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_add_i8u_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_addSquare_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_addSquare_i8u_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_addSquare_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_addSquare_i8u_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_addWeight_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_addWeight_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_addWeight_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_addWeight_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_and_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_and_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_and_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_and_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_box_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_box_3x3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_box_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_box_3x3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u/bam_plugin/BAM_VXLIB_cannyNMS_i16s_i16s_i16u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u/bam_plugin/BAM_VXLIB_cannyNMS_i16s_i16s_i16u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelCopy_1to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCopy_1to1_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelCopy_1to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCopy_1to1_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelCombine_2to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_2to1_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelCombine_2to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_2to1_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelCombine_3to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_3to1_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelCombine_3to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_3to1_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelCombine_4to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_4to1_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelCombine_4to1_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_4to1_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelCombine_yuyv_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_yuyv_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelCombine_yuyv_i8u_o8u/bam_plugin/BAM_VXLIB_channelCombine_yuyv_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of2_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of2_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of2_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of2_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of3_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of3_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of4_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of4_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_channelExtract_1of4_i8u_o8u/bam_plugin/BAM_VXLIB_channelExtract_1of4_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoNV12_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoNV12_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u/bam_plugin/BAM_VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_convertDepth_i16s_o8u/bam_plugin/BAM_VXLIB_convertDepth_i16s_o8u_exec_funcs.c\
    ./src/vx/VXLIB_convertDepth_i16s_o8u/bam_plugin/BAM_VXLIB_convertDepth_i16s_o8u_helper_funcs.c\
    ./src/vx/VXLIB_convertDepth_i8u_o16s/bam_plugin/BAM_VXLIB_convertDepth_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_convertDepth_i8u_o16s/bam_plugin/BAM_VXLIB_convertDepth_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o16s/bam_plugin/BAM_VXLIB_convolve_i8u_c16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o16s/bam_plugin/BAM_VXLIB_convolve_i8u_c16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o8u/bam_plugin/BAM_VXLIB_convolve_i8u_c16s_o8u_exec_funcs.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o8u/bam_plugin/BAM_VXLIB_convolve_i8u_c16s_o8u_helper_funcs.c\
    ./src/vx/VXLIB_dilate_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_dilate_3x3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_dilate_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_dilate_3x3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_dilate_MxN_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_dilate_MxN_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_doubleThreshold_i16u_i8u/bam_plugin/BAM_VXLIB_doubleThreshold_i16u_i8u_exec_funcs.c\
    ./src/vx/VXLIB_doubleThreshold_i16u_i8u/bam_plugin/BAM_VXLIB_doubleThreshold_i16u_i8u_helper_funcs.c\
    ./src/vx/VXLIB_erode_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_erode_3x3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_erode_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_erode_3x3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_erode_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_erode_MxN_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_erode_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_erode_MxN_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_gaussian_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_gaussian_3x3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_gaussian_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_gaussian_3x3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u/bam_plugin/BAM_VXLIB_halfScaleGaussian_5x5_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u/bam_plugin/BAM_VXLIB_halfScaleGaussian_5x5_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f/bam_plugin/BAM_VXLIB_harrisCornersScore_i16s_i16s_o32f_exec_funcs.c\
    ./src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f/bam_plugin/BAM_VXLIB_harrisCornersScore_i16s_i16s_o32f_helper_funcs.c\
    ./src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f/bam_plugin/BAM_VXLIB_harrisCornersScore_i32s_i32s_o32f_exec_funcs.c\
    ./src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f/bam_plugin/BAM_VXLIB_harrisCornersScore_i32s_i32s_o32f_helper_funcs.c\
    ./src/vx/VXLIB_histogram_i8u_o32u/bam_plugin/BAM_VXLIB_histogram_i8u_o32u_exec_funcs.c\
    ./src/vx/VXLIB_histogram_i8u_o32u/bam_plugin/BAM_VXLIB_histogram_i8u_o32u_helper_funcs.c\
    ./src/vx/VXLIB_histogramSimple_i8u_o32u/bam_plugin/BAM_VXLIB_histogramSimple_i8u_o32u_exec_funcs.c\
    ./src/vx/VXLIB_histogramSimple_i8u_o32u/bam_plugin/BAM_VXLIB_histogramSimple_i8u_o32u_helper_funcs.c\
    ./src/vx/VXLIB_integralImage_i8u_o32u/bam_plugin/BAM_VXLIB_integralImage_i8u_o32u_exec_funcs.c\
    ./src/vx/VXLIB_integralImage_i8u_o32u/bam_plugin/BAM_VXLIB_integralImage_i8u_o32u_helper_funcs.c\
    ./src/vx/VXLIB_magnitude_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_magnitude_i16s_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_magnitude_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_magnitude_i16s_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_meanStdDev_i8u_o32f/bam_plugin/BAM_VXLIB_meanStdDev_i8u_o32f_exec_funcs.c\
    ./src/vx/VXLIB_meanStdDev_i8u_o32f/bam_plugin/BAM_VXLIB_meanStdDev_i8u_o32f_helper_funcs.c\
    ./src/vx/VXLIB_median_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_median_3x3_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_median_3x3_i8u_o8u/bam_plugin/BAM_VXLIB_median_3x3_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_median_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_median_MxN_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_median_MxN_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_median_MxN_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_minMaxLoc_i16s/bam_plugin/BAM_VXLIB_minMaxLoc_i16s_exec_funcs.c\
    ./src/vx/VXLIB_minMaxLoc_i16s/bam_plugin/BAM_VXLIB_minMaxLoc_i16s_helper_funcs.c\
    ./src/vx/VXLIB_minMaxLoc_i8u/bam_plugin/BAM_VXLIB_minMaxLoc_i8u_exec_funcs.c\
    ./src/vx/VXLIB_minMaxLoc_i8u/bam_plugin/BAM_VXLIB_minMaxLoc_i8u_helper_funcs.c\
    ./src/vx/VXLIB_multiply_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_multiply_i16s_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_multiply_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_multiply_i16s_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_multiply_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_multiply_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_multiply_i8u_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_multiply_i8u_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_multiply_i8u_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_multiply_i8u_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_normL1_i16s_i16s_o16u/bam_plugin/BAM_VXLIB_normL1_i16s_i16s_o16u_exec_funcs.c\
    ./src/vx/VXLIB_normL1_i16s_i16s_o16u/bam_plugin/BAM_VXLIB_normL1_i16s_i16s_o16u_helper_funcs.c\
    ./src/vx/VXLIB_normL2_i16s_i16s_o16u/bam_plugin/BAM_VXLIB_normL2_i16s_i16s_o16u_exec_funcs.c\
    ./src/vx/VXLIB_normL2_i16s_i16s_o16u/bam_plugin/BAM_VXLIB_normL2_i16s_i16s_o16u_helper_funcs.c\
    ./src/vx/VXLIB_not_i8u_o8u/bam_plugin/BAM_VXLIB_not_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_not_i8u_o8u/bam_plugin/BAM_VXLIB_not_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_or_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_or_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_or_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_or_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_phase_i16s_i16s_o8u/bam_plugin/BAM_VXLIB_phase_i16s_i16s_o8u_exec_funcs.c\
    ./src/vx/VXLIB_phase_i16s_i16s_o8u/bam_plugin/BAM_VXLIB_phase_i16s_i16s_o8u_helper_funcs.c\
    ./src/vx/VXLIB_scaleImageNearest_i8u_o8u/bam_plugin/BAM_VXLIB_scaleImageNearest_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_scaleImageNearest_i8u_o8u/bam_plugin/BAM_VXLIB_scaleImageNearest_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_sobelX_3x3_i8u_o16s/bam_plugin/BAM_VXLIB_sobelX_3x3_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_sobelX_3x3_i8u_o16s/bam_plugin/BAM_VXLIB_sobelX_3x3_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_sobelY_3x3_i8u_o16s/bam_plugin/BAM_VXLIB_sobelY_3x3_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_sobelY_3x3_i8u_o16s/bam_plugin/BAM_VXLIB_sobelY_3x3_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_3x3_i8u_o16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_3x3_i8u_o16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_5x5_i8u_o16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_5x5_i8u_o16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_7x7_i8u_o16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s/bam_plugin/BAM_VXLIB_sobel_7x7_i8u_o16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s/bam_plugin/BAM_VXLIB_sobel_7x7_i8u_o32s_o32s_exec_funcs.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s/bam_plugin/BAM_VXLIB_sobel_7x7_i8u_o32s_o32s_helper_funcs.c\
    ./src/vx/VXLIB_subtract_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_subtract_i16s_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_subtract_i16s_i16s_o16s/bam_plugin/BAM_VXLIB_subtract_i16s_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_subtract_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_subtract_i8u_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_subtract_i8u_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i16s_o16s/bam_plugin/BAM_VXLIB_subtract_i8u_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_subtract_i8u_i8u_o16s_exec_funcs.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o16s/bam_plugin/BAM_VXLIB_subtract_i8u_i8u_o16s_helper_funcs.c\
    ./src/vx/VXLIB_tableLookup_i16s_o16s/bam_plugin/BAM_VXLIB_tableLookup_i16s_o16s_exec_funcs.c\
    ./src/vx/VXLIB_tableLookup_i16s_o16s/bam_plugin/BAM_VXLIB_tableLookup_i16s_o16s_helper_funcs.c\
    ./src/vx/VXLIB_tableLookup_i8u_o8u/bam_plugin/BAM_VXLIB_tableLookup_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_tableLookup_i8u_o8u/bam_plugin/BAM_VXLIB_tableLookup_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_thresholdBinary_i8u_o8u/bam_plugin/BAM_VXLIB_thresholdBinary_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_thresholdBinary_i8u_o8u/bam_plugin/BAM_VXLIB_thresholdBinary_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_thresholdRange_i8u_o8u/bam_plugin/BAM_VXLIB_thresholdRange_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_thresholdRange_i8u_o8u/bam_plugin/BAM_VXLIB_thresholdRange_i8u_o8u_helper_funcs.c\
    ./src/vx/VXLIB_xor_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_xor_i8u_i8u_o8u_exec_funcs.c\
    ./src/vx/VXLIB_xor_i8u_i8u_o8u/bam_plugin/BAM_VXLIB_xor_i8u_i8u_o8u_helper_funcs.c

# FLAGS for the kernelBamc66Host Files
KERNELBAMC66HOSTCFLAGS =  -Ot -Zi -DTMS320C66X -D_TMS320C6600 -D_HOST_BUILD -DCORE_DSP -DHOST_EMULATION

# Make Rule for the kernelBamc66Host Files
KERNELBAMC66HOSTCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELBAMC66HOSTC))

$(KERNELBAMC66HOSTCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cl86 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(CC) $(KERNELBAMC66HOSTCFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) $< 

#Create Empty rule for dependency
$(KERNELBAMC66HOSTCOBJS):lib\vxlib_bamplugin.a86.mk
lib\vxlib_bamplugin.a86.mk:

#Include Depedency for kernelBamc66Host Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELBAMC66HOSTCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/vxlib_bamplugin.a86 : $(KERNELBAMC66HOSTCOBJS)
	@echo archiving $? into $@ ...
	@echo "-nologo -out:$@ $^">$@.cmd
	$(ARIN) @$@.cmd
