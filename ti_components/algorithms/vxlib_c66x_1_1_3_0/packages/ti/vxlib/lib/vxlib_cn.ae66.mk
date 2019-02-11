#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/vxlib_cn.ae66.mk
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
OBJDIR = ./package/lib/lib/vxlib_cnae66


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  OPTFLAGS = -g
else
  OPTFLAGS = -o3 --symdebug:none
endif



#List the kernelc66 Files
KERNELC66C= \
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

# FLAGS for the kernelc66 Files
KERNELC66CFLAGS =  -c -k -mw --strip_coff_underscore $(OPTFLAGS) --mem_model:data=far --legacy

# Make Rule for the kernelc66 Files
KERNELC66COBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66C))

$(KERNELC66COBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cle66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(KERNELC66CFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(KERNELC66COBJS):lib\vxlib_cn.ae66.mk
lib\vxlib_cn.ae66.mk:

#Include Depedency for kernelc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66COBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif

#List the kernelNatcc66 Files
KERNELNATCC66C= \
    ./src/vx/VXLIB_absDiff_i16s_i16s_o16s/VXLIB_absDiff_i16s_i16s_o16s_cn.c\
    ./src/vx/VXLIB_absDiff_i8u_i8u_o8u/VXLIB_absDiff_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_accumulateImage_i8u_io16s/VXLIB_accumulateImage_i8u_io16s_cn.c\
    ./src/vx/VXLIB_accumulateSquareImage_i8u_io16s/VXLIB_accumulateSquareImage_i8u_io16s_cn.c\
    ./src/vx/VXLIB_accumulateWeightedImage_i8u_io8u/VXLIB_accumulateWeightedImage_i8u_io8u_cn.c\
    ./src/vx/VXLIB_add_i16s_i16s_o16s/VXLIB_add_i16s_i16s_o16s_cn.c\
    ./src/vx/VXLIB_add_i8u_i8u_o8u/VXLIB_add_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_add_i8u_i16s_o16s/VXLIB_add_i8u_i16s_o16s_cn.c\
    ./src/vx/VXLIB_add_i8u_i8u_o16s/VXLIB_add_i8u_i8u_o16s_cn.c\
    ./src/vx/VXLIB_addSquare_i8u_i16s_o16s/VXLIB_addSquare_i8u_i16s_o16s_cn.c\
    ./src/vx/VXLIB_addWeight_i8u_i8u_o8u/VXLIB_addWeight_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_and_i8u_i8u_o8u/VXLIB_and_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_box_3x3_i8u_o8u/VXLIB_box_3x3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_cannyNMS_i16s_i16s_i16u_o8u/VXLIB_cannyNMS_i16s_i16s_i16u_o8u_cn.c\
    ./src/vx/VXLIB_channelCopy_1to1_i8u_o8u/VXLIB_channelCopy_1to1_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelCombine_2to1_i8u_o8u/VXLIB_channelCombine_2to1_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelCombine_3to1_i8u_o8u/VXLIB_channelCombine_3to1_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelCombine_4to1_i8u_o8u/VXLIB_channelCombine_4to1_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelCombine_yuyv_i8u_o8u/VXLIB_channelCombine_yuyv_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelExtract_1of2_i8u_o8u/VXLIB_channelExtract_1of2_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelExtract_1of3_i8u_o8u/VXLIB_channelExtract_1of3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_channelExtract_1of4_i8u_o8u/VXLIB_channelExtract_1of4_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u/VXLIB_colorConvert_IYUVtoNV12_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u/VXLIB_colorConvert_IYUVtoRGB_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u/VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u/VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u/VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u/VXLIB_colorConvert_NVXXtoRGB_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u/VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u/VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u/VXLIB_colorConvert_RGBtoIYUV_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBtoNV12_i8u_o8u/VXLIB_colorConvert_RGBtoNV12_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u/VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u/VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u/VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u/VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u/VXLIB_colorConvert_RGBXtoRGB_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u/VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u/VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u/VXLIB_colorConvert_YUVXtoRGB_i8u_o8u_cn.c\
    ./src/vx/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u/VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_cn.c\
    ./src/vx/VXLIB_convertDepth_i16s_o8u/VXLIB_convertDepth_i16s_o8u_cn.c\
    ./src/vx/VXLIB_convertDepth_i8u_o16s/VXLIB_convertDepth_i8u_o16s_cn.c\
    ./src/vx/VXLIB_convolve_3x3_i8u_c16s_o16s/VXLIB_convolve_3x3_i8u_c16s_o16s_cn.c\
    ./src/vx/VXLIB_convolve_3x3_i8u_c16s_o8u/VXLIB_convolve_3x3_i8u_c16s_o8u_cn.c\
    ./src/vx/VXLIB_convolve_5x5_i8u_c16s_o16s/VXLIB_convolve_5x5_i8u_c16s_o16s_cn.c\
    ./src/vx/VXLIB_convolve_5x5_i8u_c16s_o8u/VXLIB_convolve_5x5_i8u_c16s_o8u_cn.c\
    ./src/vx/VXLIB_convolve_7x7_i8u_c16s_o16s/VXLIB_convolve_7x7_i8u_c16s_o16s_cn.c\
    ./src/vx/VXLIB_convolve_7x7_i8u_c16s_o8u/VXLIB_convolve_7x7_i8u_c16s_o8u_cn.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o16s/VXLIB_convolve_i8u_c16s_o16s_cn.c\
    ./src/vx/VXLIB_convolve_i8u_c16s_o8u/VXLIB_convolve_i8u_c16s_o8u_cn.c\
    ./src/vx/VXLIB_dilate_3x3_i8u_o8u/VXLIB_dilate_3x3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_dilate_MxN_i8u_i8u_o8u/VXLIB_dilate_MxN_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_doubleThreshold_i16u_i8u/VXLIB_doubleThreshold_i16u_i8u_cn.c\
    ./src/vx/VXLIB_edgeTracing_i8u/VXLIB_edgeTracing_i8u_cn.c\
    ./src/vx/VXLIB_equalizeHist_i8u_o8u/VXLIB_equalizeHist_i8u_o8u_cn.c\
    ./src/vx/VXLIB_erode_3x3_i8u_o8u/VXLIB_erode_3x3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_erode_MxN_i8u_i8u_o8u/VXLIB_erode_MxN_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_fastCorners_i8u/VXLIB_fastCorners_i8u_cn.c\
    ./src/vx/VXLIB_fastCornersDetect_i8u/VXLIB_fastCornersDetect_i8u_cn.c\
    ./src/vx/VXLIB_fastCornersScore_i8u/VXLIB_fastCornersScore_i8u_cn.c\
    ./src/vx/VXLIB_fastCornersNMS_i8u/VXLIB_fastCornersNMS_i8u_cn.c\
    ./src/vx/VXLIB_gaussian_3x3_i8u_o8u/VXLIB_gaussian_3x3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_gaussian_5x5_br_i8u_o8u/VXLIB_gaussian_5x5_br_i8u_o8u_cn.c\
    ./src/vx/VXLIB_gaussian_5x5_i8u_o8u/VXLIB_gaussian_5x5_i8u_o8u_cn.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u/VXLIB_halfScaleGaussian_5x5_i8u_o8u_cn.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u/VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u_cn.c\
    ./src/vx/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u/VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u_cn.c\
    ./src/vx/VXLIB_harrisCornersDetect_i32f/VXLIB_harrisCornersDetect_i32f_cn.c\
    ./src/vx/VXLIB_harrisCornersNMS_i32f/VXLIB_harrisCornersNMS_i32f_cn.c\
    ./src/vx/VXLIB_harrisCornersScore_i16s_i16s_o32f/VXLIB_harrisCornersScore_i16s_i16s_o32f_cn.c\
    ./src/vx/VXLIB_harrisCornersScore_i32s_i32s_o32f/VXLIB_harrisCornersScore_i32s_i32s_o32f_cn.c\
    ./src/vx/VXLIB_histogram_i8u_o32u/VXLIB_histogram_i8u_o32u_cn.c\
    ./src/vx/VXLIB_histogramCdfLut_i32u_o8u/VXLIB_histogramCdfLut_i32u_o8u_cn.c\
    ./src/vx/VXLIB_histogramSimple_i8u_o32u/VXLIB_histogramSimple_i8u_o32u_cn.c\
    ./src/vx/VXLIB_integralImage_i8u_o32u/VXLIB_integralImage_i8u_o32u_cn.c\
    ./src/vx/VXLIB_magnitude_i16s_i16s_o16s/VXLIB_magnitude_i16s_i16s_o16s_cn.c\
    ./src/vx/VXLIB_meanStdDev_i8u_o32f/VXLIB_meanStdDev_i8u_o32f_cn.c\
    ./src/vx/VXLIB_median_3x3_i8u_o8u/VXLIB_median_3x3_i8u_o8u_cn.c\
    ./src/vx/VXLIB_median_MxN_i8u_i8u_o8u/VXLIB_median_MxN_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_minMaxLoc_i16s/VXLIB_minMaxLoc_i16s_cn.c\
    ./src/vx/VXLIB_minMaxLoc_i8u/VXLIB_minMaxLoc_i8u_cn.c\
    ./src/vx/VXLIB_multiply_i16s_i16s_o16s/VXLIB_multiply_i16s_i16s_o16s_cn.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o8u/VXLIB_multiply_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_multiply_i8u_i16s_o16s/VXLIB_multiply_i8u_i16s_o16s_cn.c\
    ./src/vx/VXLIB_multiply_i8u_i8u_o16s/VXLIB_multiply_i8u_i8u_o16s_cn.c\
    ./src/vx/VXLIB_normL1_i16s_i16s_o16u/VXLIB_normL1_i16s_i16s_o16u_cn.c\
    ./src/vx/VXLIB_normL2_i16s_i16s_o16u/VXLIB_normL2_i16s_i16s_o16u_cn.c\
    ./src/vx/VXLIB_not_i8u_o8u/VXLIB_not_i8u_o8u_cn.c\
    ./src/vx/VXLIB_or_i8u_i8u_o8u/VXLIB_or_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_phase_i16s_i16s_o8u/VXLIB_phase_i16s_i16s_o8u_cn.c\
    ./src/vx/VXLIB_remapBilinear_bc_i8u_i32f_o8u/VXLIB_remapBilinear_bc_i8u_i32f_o8u_cn.c\
    ./src/vx/VXLIB_remapNearest_bc_i8u_i32f_o8u/VXLIB_remapNearest_bc_i8u_i32f_o8u_cn.c\
    ./src/vx/VXLIB_scaleImageBilinear_i8u_o8u/VXLIB_scaleImageBilinear_i8u_o8u_cn.c\
    ./src/vx/VXLIB_scaleImageBilinear_bc_i8u_o8u/VXLIB_scaleImageBilinear_bc_i8u_o8u_cn.c\
    ./src/vx/VXLIB_scaleImageBilinear_br_i8u_o8u/VXLIB_scaleImageBilinear_br_i8u_o8u_cn.c\
    ./src/vx/VXLIB_scaleImageNearest_i8u_o8u/VXLIB_scaleImageNearest_i8u_o8u_cn.c\
    ./src/vx/VXLIB_scharr_3x3_i8u_o16s_o16s/VXLIB_scharr_3x3_i8u_o16s_o16s_cn.c\
    ./src/vx/VXLIB_sobelX_3x3_i8u_o16s/VXLIB_sobelX_3x3_i8u_o16s_cn.c\
    ./src/vx/VXLIB_sobelY_3x3_i8u_o16s/VXLIB_sobelY_3x3_i8u_o16s_cn.c\
    ./src/vx/VXLIB_sobel_3x3_i8u_o16s_o16s/VXLIB_sobel_3x3_i8u_o16s_o16s_cn.c\
    ./src/vx/VXLIB_sobel_5x5_i8u_o16s_o16s/VXLIB_sobel_5x5_i8u_o16s_o16s_cn.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o16s_o16s/VXLIB_sobel_7x7_i8u_o16s_o16s_cn.c\
    ./src/vx/VXLIB_sobel_7x7_i8u_o32s_o32s/VXLIB_sobel_7x7_i8u_o32s_o32s_cn.c\
    ./src/vx/VXLIB_subtract_i16s_i16s_o16s/VXLIB_subtract_i16s_i16s_o16s_cn.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o8u/VXLIB_subtract_i8u_i8u_o8u_cn.c\
    ./src/vx/VXLIB_subtract_i8u_i16s_o16s/VXLIB_subtract_i8u_i16s_o16s_cn.c\
    ./src/vx/VXLIB_subtract_i8u_i8u_o16s/VXLIB_subtract_i8u_i8u_o16s_cn.c\
    ./src/vx/VXLIB_tableLookup_i16s_o16s/VXLIB_tableLookup_i16s_o16s_cn.c\
    ./src/vx/VXLIB_tableLookup_i8u_o8u/VXLIB_tableLookup_i8u_o8u_cn.c\
    ./src/vx/VXLIB_thresholdBinary_i8u_o8u/VXLIB_thresholdBinary_i8u_o8u_cn.c\
    ./src/vx/VXLIB_thresholdRange_i8u_o8u/VXLIB_thresholdRange_i8u_o8u_cn.c\
    ./src/vx/VXLIB_trackFeaturesLK_i8u/VXLIB_trackFeaturesLK_i8u_cn.c\
    ./src/vx/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u/VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpAffineBilinear_i8u_c32f_o8u/VXLIB_warpAffineBilinear_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u/VXLIB_warpAffineNearest_bc_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpAffineNearest_i8u_c32f_o8u/VXLIB_warpAffineNearest_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u/VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u/VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u/VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u/VXLIB_warpPerspectiveNearest_i8u_c32f_o8u_cn.c\
    ./src/vx/VXLIB_xor_i8u_i8u_o8u/VXLIB_xor_i8u_i8u_o8u_cn.c

# FLAGS for the kernelNatcc66 Files
KERNELNATCC66CFLAGS =  -c -k -mw --strip_coff_underscore $(OPTFLAGS) --mem_model:data=far --legacy

# Make Rule for the kernelNatcc66 Files
KERNELNATCC66COBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELNATCC66C))

$(KERNELNATCC66COBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cle66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(KERNELNATCC66CFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(KERNELNATCC66COBJS):lib\vxlib_cn.ae66.mk
lib\vxlib_cn.ae66.mk:

#Include Depedency for kernelNatcc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELNATCC66COBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/vxlib_cn.ae66 : $(KERNELC66COBJS) $(KERNELNATCC66COBJS)
	@echo archiving $? into $@ ...
	@echo "rq $@ $?">$@.cmd
	$(ARIN) @$@.cmd
	if [ -f $(@D)/vxlib_cn.lib  ]; then $(LIBINFO) -u -o=$(@D)/vxlib_cn.lib $@; else $(LIBINFO) -o=$(@D)/vxlib_cn.lib $@; fi;
