#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/vxlib.a86l.mk
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
CC = gcc -c
AC = gcc -c
ARIN = ar
LD = g++
CGINCS =
RTSLIB =
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = o86l
AOBJEXT = s86l
INTERNALDEFS = -std=c99 -DHOST_EMULATION -m32
INTERNALLINKDEFS =  -map:$@.map -pdb:$@.pdb -out:$@ 
OBJDIR = ./package/lib/lib/vxliba86l


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  CC += -ggdb -ggdb3 -gdwarf-2
  INTERNALLINKDEFS += -DEBUG
else
  CC += -O3
endif


INTERNALLINKDEFS +=

#List the kernelc66Host Files
KERNELC66HOSTC= \
    ./src/vx/VXLIB_absDiff_i16s_i16s_o16s//c66/VXLIB_absDiff_i16s_i16s_o16s.c\
    ./src/vx/VXLIB_absDiff_i8u_i8u_o8u//c66/VXLIB_absDiff_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_accumulateImage_i8u_io16s//c66/VXLIB_accumulateImage_i8u_io16s.c\
    ./src/vx/VXLIB_accumulateSquareImage_i8u_io16s//c66/VXLIB_accumulateSquareImage_i8u_io16s.c\
    ./src/vx/VXLIB_accumulateWeightedImage_i8u_io8u//c66/VXLIB_accumulateWeightedImage_i8u_io8u.c\
    ./src/vx/VXLIB_add_i16s_i16s_o16s//c66/VXLIB_add_i16s_i16s_o16s.c\
    ./src/vx/VXLIB_add_i8u_i8u_o8u//c66/VXLIB_add_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_add_i8u_i16s_o16s//c66/VXLIB_add_i8u_i16s_o16s.c\
    ./src/vx/VXLIB_add_i8u_i8u_o16s//c66/VXLIB_add_i8u_i8u_o16s.c\
    ./src/vx/VXLIB_addSquare_i8u_i16s_o16s//c66/VXLIB_addSquare_i8u_i16s_o16s.c\
    ./src/vx/VXLIB_addWeight_i8u_i8u_o8u//c66/VXLIB_addWeight_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_and_i8u_i8u_o8u//c66/VXLIB_and_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_box_3x3_i8u_o8u//c66/VXLIB_box_3x3_i8u_o8u.c\
    ./src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u//c66/VXLIB_cannyNMS_i16s_i16s_i16u_o8u.c\
    ./src/vx/VXLIB_channelCopy_1to1_i8u_o8u//c66/VXLIB_channelCopy_1to1_i8u_o8u.c\
    ./src/vx/VXLIB_channelCombine_2to1_i8u_o8u//c66/VXLIB_channelCombine_2to1_i8u_o8u.c\
    ./src/vx/VXLIB_channelCombine_3to1_i8u_o8u//c66/VXLIB_channelCombine_3to1_i8u_o8u.c\
    ./src/vx/VXLIB_channelCombine_4to1_i8u_o8u//c66/VXLIB_channelCombine_4to1_i8u_o8u.c\
    ./src/vx/VXLIB_channelCombine_yuyv_i8u_o8u//c66/VXLIB_channelCombine_yuyv_i8u_o8u.c\
    ./src/vx/VXLIB_channelExtract_1of2_i8u_o8u//c66/VXLIB_channelExtract_1of2_i8u_o8u.c\
    ./src/vx/VXLIB_channelExtract_1of3_i8u_o8u//c66/VXLIB_channelExtract_1of3_i8u_o8u.c\
    ./src/vx/VXLIB_channelExtract_1of4_i8u_o8u//c66/VXLIB_channelExtract_1of4_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u//c66/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u//c66/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u//c66/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u//c66/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u//c66/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u//c66/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u//c66/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u//c66/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u//c66/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u//c66/VXLIB_colorConvert_RGBtoNV12_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u//c66/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u//c66/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u//c66/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u//c66/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u//c66/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u//c66/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u//c66/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u//c66/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u//c66/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u//c66/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u.c\
    ./src/vx/VXLIB_convertDepth_i16s_o8u//c66/VXLIB_convertDepth_i16s_o8u.c\
    ./src/vx/VXLIB_convertDepth_i8u_o16s//c66/VXLIB_convertDepth_i8u_o16s.c\
    ./src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s//c66/VXLIB_convolve_3x3_i8u_c16s_o16s.c\
    ./src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u//c66/VXLIB_convolve_3x3_i8u_c16s_o8u.c\
    ./src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s//c66/VXLIB_convolve_5x5_i8u_c16s_o16s.c\
    ./src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u//c66/VXLIB_convolve_5x5_i8u_c16s_o8u.c\
    ./src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s//c66/VXLIB_convolve_7x7_i8u_c16s_o16s.c\
    ./src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u//c66/VXLIB_convolve_7x7_i8u_c16s_o8u.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o16s//c66/VXLIB_convolve_i8u_c16s_o16s.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o8u//c66/VXLIB_convolve_i8u_c16s_o8u.c\
    ./src/vx/VXLIB_dilate_3x3_i8u_o8u//c66/VXLIB_dilate_3x3_i8u_o8u.c\
    ./src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u//c66/VXLIB_dilate_MxN_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_doubleThreshold_i16u_i8u//c66/VXLIB_doubleThreshold_i16u_i8u.c\
    ./src/vx/VXLIB_edgeTracing_i8u//c66/VXLIB_edgeTracing_i8u.c\
    ./src/vx/VXLIB_equalizeHist_i8u_o8u//c66/VXLIB_equalizeHist_i8u_o8u.c\
    ./src/vx/VXLIB_erode_3x3_i8u_o8u//c66/VXLIB_erode_3x3_i8u_o8u.c\
    ./src/vx/VXLIB_erode_MxN_i8u_i8u_o8u//c66/VXLIB_erode_MxN_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_fastCorners_i8u//c66/VXLIB_fastCorners_i8u.c\
    ./src/vx/VXLIB_fastCornersDetect_i8u//c66/VXLIB_fastCornersDetect_i8u.c\
    ./src/vx/VXLIB_fastCornersScore_i8u//c66/VXLIB_fastCornersScore_i8u.c\
    ./src/vx/VXLIB_fastCornersNMS_i8u//c66/VXLIB_fastCornersNMS_i8u.c\
    ./src/vx/VXLIB_gaussian_3x3_i8u_o8u//c66/VXLIB_gaussian_3x3_i8u_o8u.c\
    ./src/vx/VXLIB_gaussian_5x5_br_i8u_o8u//c66/VXLIB_gaussian_5x5_br_i8u_o8u.c\
    ./src/vx/VXLIB_gaussian_5x5_i8u_o8u//c66/VXLIB_gaussian_5x5_i8u_o8u.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u//c66/VXLIB_halfScaleGaussian_5x5_i8u_o8u.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u//c66/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u//c66/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u.c\
    ./src/vx/VXLIB_harrisCornersDetect_i32f//c66/VXLIB_harrisCornersDetect_i32f.c\
    ./src/vx/VXLIB_harrisCornersNMS_i32f//c66/VXLIB_harrisCornersNMS_i32f.c\
    ./src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f//c66/VXLIB_harrisCornersScore_i16s_i16s_o32f.c\
    ./src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f//c66/VXLIB_harrisCornersScore_i32s_i32s_o32f.c\
    ./src/vx/VXLIB_histogram_i8u_o32u//c66/VXLIB_histogram_i8u_o32u.c\
    ./src/vx/VXLIB_histogramCdfLut_i32u_o8u//c66/VXLIB_histogramCdfLut_i32u_o8u.c\
    ./src/vx/VXLIB_histogramSimple_i8u_o32u//c66/VXLIB_histogramSimple_i8u_o32u.c\
    ./src/vx/VXLIB_integralImage_i8u_o32u//c66/VXLIB_integralImage_i8u_o32u.c\
    ./src/vx/VXLIB_magnitude_i16s_i16s_o16s//c66/VXLIB_magnitude_i16s_i16s_o16s.c\
    ./src/vx/VXLIB_meanStdDev_i8u_o32f//c66/VXLIB_meanStdDev_i8u_o32f.c\
    ./src/vx/VXLIB_median_3x3_i8u_o8u//c66/VXLIB_median_3x3_i8u_o8u.c\
    ./src/vx/VXLIB_median_MxN_i8u_i8u_o8u//c66/VXLIB_median_MxN_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_minMaxLoc_i16s//c66/VXLIB_minMaxLoc_i16s.c\
    ./src/vx/VXLIB_minMaxLoc_i8u//c66/VXLIB_minMaxLoc_i8u.c\
    ./src/vx/VXLIB_multiply_i16s_i16s_o16s//c66/VXLIB_multiply_i16s_i16s_o16s.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o8u//c66/VXLIB_multiply_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_multiply_i8u_i16s_o16s//c66/VXLIB_multiply_i8u_i16s_o16s.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o16s//c66/VXLIB_multiply_i8u_i8u_o16s.c\
    ./src/vx/VXLIB_normL1_i16s_i16s_o16u//c66/VXLIB_normL1_i16s_i16s_o16u.c\
    ./src/vx/VXLIB_normL2_i16s_i16s_o16u//c66/VXLIB_normL2_i16s_i16s_o16u.c\
    ./src/vx/VXLIB_not_i8u_o8u//c66/VXLIB_not_i8u_o8u.c\
    ./src/vx/VXLIB_or_i8u_i8u_o8u//c66/VXLIB_or_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_phase_i16s_i16s_o8u//c66/VXLIB_phase_i16s_i16s_o8u.c\
    ./src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u//c66/VXLIB_remapBilinear_bc_i8u_i32f_o8u.c\
    ./src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u//c66/VXLIB_remapNearest_bc_i8u_i32f_o8u.c\
    ./src/vx/VXLIB_scaleImageBilinear_i8u_o8u//c66/VXLIB_scaleImageBilinear_i8u_o8u.c\
    ./src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u//c66/VXLIB_scaleImageBilinear_bc_i8u_o8u.c\
    ./src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u//c66/VXLIB_scaleImageBilinear_br_i8u_o8u.c\
    ./src/vx/VXLIB_scaleImageNearest_i8u_o8u//c66/VXLIB_scaleImageNearest_i8u_o8u.c\
    ./src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s//c66/VXLIB_scharr_3x3_i8u_o16s_o16s.c\
    ./src/vx/VXLIB_sobelX_3x3_i8u_o16s//c66/VXLIB_sobelX_3x3_i8u_o16s.c\
    ./src/vx/VXLIB_sobelY_3x3_i8u_o16s//c66/VXLIB_sobelY_3x3_i8u_o16s.c\
    ./src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s//c66/VXLIB_sobel_3x3_i8u_o16s_o16s.c\
    ./src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s//c66/VXLIB_sobel_5x5_i8u_o16s_o16s.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s//c66/VXLIB_sobel_7x7_i8u_o16s_o16s.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s//c66/VXLIB_sobel_7x7_i8u_o32s_o32s.c\
    ./src/vx/VXLIB_subtract_i16s_i16s_o16s//c66/VXLIB_subtract_i16s_i16s_o16s.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o8u//c66/VXLIB_subtract_i8u_i8u_o8u.c\
    ./src/vx/VXLIB_subtract_i8u_i16s_o16s//c66/VXLIB_subtract_i8u_i16s_o16s.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o16s//c66/VXLIB_subtract_i8u_i8u_o16s.c\
    ./src/vx/VXLIB_tableLookup_i16s_o16s//c66/VXLIB_tableLookup_i16s_o16s.c\
    ./src/vx/VXLIB_tableLookup_i8u_o8u//c66/VXLIB_tableLookup_i8u_o8u.c\
    ./src/vx/VXLIB_thresholdBinary_i8u_o8u//c66/VXLIB_thresholdBinary_i8u_o8u.c\
    ./src/vx/VXLIB_thresholdRange_i8u_o8u//c66/VXLIB_thresholdRange_i8u_o8u.c\
    ./src/vx/VXLIB_trackFeaturesLK_i8u//c66/VXLIB_trackFeaturesLK_i8u.c\
    ./src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u//c66/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u//c66/VXLIB_warpAffineBilinear_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u//c66/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u//c66/VXLIB_warpAffineNearest_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u//c66/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u//c66/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u//c66/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u//c66/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u.c\
    ./src/vx/VXLIB_xor_i8u_i8u_o8u//c66/VXLIB_xor_i8u_i8u_o8u.c

# FLAGS for the kernelc66Host Files
KERNELC66HOSTCFLAGS =  -DTMS320C66X -D_TMS320C6600 -DLITTLE_ENDIAN_HOST -D_LITTLE_ENDIAN  -D_HOST_BUILD -Icommon/c6xsim

# Make Rule for the kernelc66Host Files
KERNELC66HOSTCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66HOSTC))

$(KERNELC66HOSTCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cl86l $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(CC) $(KERNELC66HOSTCFLAGS) $(INTERNALDEFS) $(INCS) -MMD -MF $@.dep -MT '$@' $< -o $@

#Create Empty rule for dependency
$(KERNELC66HOSTCOBJS):lib\vxlib.a86l.mk
lib\vxlib.a86l.mk:

#Include Depedency for kernelc66Host Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66HOSTCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/vxlib.a86l : $(KERNELC66HOSTCOBJS)
	@echo archiving $? into $@ ...
	@echo "-rscu $@ $^">$@.cmd
	$(ARIN) @$@.cmd
